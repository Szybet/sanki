#include "mainMenu/mainWindow.h"
#include "cardView/deckPlay.h"
#include "mainMenu/decks/deck.cpp"
#include "mainMenu/sessions/session.h"
#include "ui_mainWindow.h"
#include "components/statusBarC.h"
#include "mainMenu/fancyGrid.h"
#include "global.h"
#include "cardView/modeOptions.h"
#include "zip.h"
#include "components/files/fileChooser.h"
#include "sessions/sessionStruct.h"
#include "components/other/askText.h"

#ifdef EREADER
#include "einkenums.h"
#include "koboplatformfunctions.h"
#endif

#include <QTime>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QInputDialog>
#include <QSettings>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Battery checking
    /*
    if(ereader) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::battery_warning_timer);
        timer->start(15000);
    }
    */

    statusBarCWidget = new statusBarC(this);
    ui->gridStatus->addWidget(statusBarCWidget);

    grid = new fancyGrid(this);
    ui->gridMain->addWidget(grid);

    playDeck = new DeckPlay(this);
    ui->gridMain->addWidget(playDeck);
    playDeck->hide();

    showSessions();

    if(directories::globalSettings.exists() == false) {
        qDebug() << "Global config doesn't exists, creating it";
        QSettings settings(directories::globalSettings.fileName(), QSettings::IniFormat);
        settings.setParent(this);
        QFont defaultFont("DejaVu Sans", 10);
        settings.setValue("playFont", defaultFont);
        // Possible values:
        // WaveForm_A2 - 4 - default that is set - speed
        // WaveForm_GC16 - 2 - The default that is used everywhere else
        // WaveForm_GC4 - 3 - less black flashing, better looking
        // WaveForm_AUTO - 257 - weird
        settings.setValue("deckPlayWaveForm", 4); // WaveForm_A2



        settings.sync();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGrid() {
    grid->reset();
    grid->disconnect();
}

void MainWindow::resetStatusBar() {
    statusBarCWidget->disconnect();
    connect(statusBarCWidget, &statusBarC::refreshDecksSignal, this, &MainWindow::updateGrid);
}

void MainWindow::showSessions() {
#ifdef EREADER
    qDebug() << "Setting waveform mode";
    KoboPlatformFunctions::setFullScreenRefreshMode(WaveForm_GC16);
#endif

    statusBarSessionAdd();

    resetGrid();

    connect(grid, &fancyGrid::addItem, this, &MainWindow::addSlotSession);

    foreach(QString file , directories::sessionSaves.entryList(QDir::NoDotAndDotDot | QDir::Files)) {
        qDebug() << "Session file:" << file;
        // Idk, those files get created only in inkbox user app, just ignore them...
        if(file.endsWith(".lock") == true) {
            continue;
        }

        session* newSession = new session(grid);
        newSession->start(file);
        connect(newSession, &session::playSession, this, &MainWindow::playSession);
        connect(newSession, &session::refreshSessionsSignal, this, &MainWindow::showSessions);

        grid->addWidget(newSession);
    }

    grid->showWidgets();
    areDecksShown = false;
}

void MainWindow::showDecks() {
    qDebug() << "Show decks called";
    deckPathList.clear();

    statusBarDeckAdd();

    resetGrid();

    connect(grid, &fancyGrid::addItem, this, &MainWindow::extractDeck);

    foreach(QString file , directories::deckStorage.entryList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        qDebug() << "Deck dir:" << file;
        deck* newDeck = new deck(grid);

        connect(newDeck, &deck::selectedDeck, this, &MainWindow::getDeck);
        connect(newDeck, &deck::refreshDecks, this, &MainWindow::showDecks);
        newDeck->start(directories::deckStorage.filePath(file));

        grid->addWidget(newDeck);
    }
    grid->showWidgets();
    areDecksShown = true;
}

void MainWindow::getDeck(QString path) {
    if(deckPathList.contains(path) == true) {
       // Manage unsetting too
        deckPathList.removeAll(path);
        qDebug() << "Removed deck:" << path;
    } else {
        deckPathList.append(path);
        qDebug() << "Added deck:" << path;
    }
}

void MainWindow::extractDeck()
{
    // Dont get confused, this is a slot activated from status bar
    if(ereader) {
        // TODO: select file type
        fileChooserCustom* fileChooserCustomDialog = new fileChooserCustom;
        fileChooserCustomDialog->start(".apkg");
        connect(fileChooserCustomDialog, &fileChooserCustom::provideFile, this, &MainWindow::getFile);
        fileChooserCustomDialog->exec();
    } else if(pc) {
        zipFilePath = QFileDialog::getOpenFileName(this, "Select anki deck", directories::fileSelect.path(), "Anki Files (*.zip *.apkg)");
    }

    if(zipFilePath.isEmpty() == true) {
        return void();
    }
    QFile zipFile{zipFilePath};
    if (zipFile.exists()) {
        qDebug() << "zip to be added exists";

        QDir newDeck;
        QFileInfo zipfileInfo(zipFilePath);
        newDeck.setPath(directories::deckStorage.path() + QDir::separator() + zipfileInfo.baseName());

        qDebug() << "new deck path: " << newDeck.path();

        directories::deckStorage.mkdir(zipfileInfo.baseName());

        // Converting to acceptable string
        const char *char_converted = zipFilePath.toLocal8Bit().data();
        int arg = 2; // why
        zip_extract(char_converted, newDeck.path().toLocal8Bit().data(), 0, &arg);

        // For deck stats
        QFile creationTime(newDeck.filePath(deckAddedFileName));
        creationTime.open(QIODevice::WriteOnly);
        creationTime.write(QDateTime::currentDateTime().toString("dd.MM.yyyy - hh:mm").toStdString().c_str());
        creationTime.close();
    } else {
        qWarning() << "File doesn't exist?:" << zipFilePath;
    }
    showDecks();
}

void MainWindow::getFile(QString file)
{
    zipFilePath = file;
    qDebug() << "Slot activated, received:" << file;
}

void MainWindow::getMode(DeckModes modeSelected)
{
    qDebug() << "Slot activated, received: " << modeSelected;
    mode = modeSelected;
}

void MainWindow::statusBarSessionAdd()
{
    resetStatusBar();

    statusBarCWidget->OptionButtonSet("Add session", QIcon(":/icons/sessionAdd.svg"), true);
    statusBarCWidget->OptionButtonSet2(nullptr, QIcon(""), false);
    connect(statusBarCWidget, &statusBarC::optionButtonSignal, this, &MainWindow::addSlotSession);

    if(ereader) {
        statusBarCWidget->OptionButtonExit(QIcon(":/icons/close.png"), true);
        connect(statusBarCWidget, &statusBarC::closeButtonSignal, this, &MainWindow::close);
    } else {
        statusBarCWidget->OptionButtonExit(QIcon(), false);
    }

    // For now not needed in statusBarDeckAdd
    statusBarCWidget->setStatusText("Sanki");
}

void MainWindow::statusBarDeckAdd() {
    resetStatusBar();

    statusBarCWidget->OptionButtonSet("Add deck", QIcon(":/icons/deckAdd.svg"), true);
    statusBarCWidget->OptionButtonSet2("Confirm", QIcon(":/icons/confirm.svg"), true);
    connect(statusBarCWidget, &statusBarC::optionButtonSignal, this, &MainWindow::extractDeck);
    connect(statusBarCWidget, &statusBarC::option2ButtonSignal, this, &MainWindow::doneSelectingDecks);

    /*
    if(ereader) {
        statusBarCWidget->OptionButtonExit(QIcon(":/icons/close.png"), true);
        connect(statusBarCWidget, &statusBarC::closeButtonSignal, this, &MainWindow::close);
    } else {
        statusBarCWidget->OptionButtonExit(QIcon(), false);
    }
    */
    statusBarCWidget->OptionButtonExit(QIcon(":/icons/back.svg"), true);
    connect(statusBarCWidget, &statusBarC::closeButtonSignal, this, &MainWindow::showSessions);
}

void MainWindow::returnToStart()
{
    qDebug() << "Resetting";
    playDeck->hide();
    grid->show();
    showSessions();
}

void MainWindow::addSlotSession() {
    qDebug() << "Session being added";
    modeChooser* chooseMode = new modeChooser;
    connect(chooseMode, SIGNAL(setMode(DeckModes)), this, SLOT(getMode(DeckModes)));
    int code = chooseMode->exec();
    qDebug() << "chooseMode dialog return value is:" << code;
    if(code != QDialog::Accepted) {
        return void();
    }

    showDecks();

    // Rest in Done selecting decks
}

void MainWindow::doneSelectingDecks() {
    qDebug() << "doneSelectingDecks called";
    if(deckPathList.isEmpty() == true) {
        qWarning() << "No decks selected";
        returnToStart();
        return void();
    }
    createSession();
}

void MainWindow::createSession() {
    // Ask for name
    bool continueCreating = true;
    QString text = "";

    if(pc) {
        text = QInputDialog::getText(this, tr("Insert text"),
                                             tr("Provide name for session"), QLineEdit::Normal,
                                             "", &continueCreating);
    }
    if(ereader) {
        askText* askTextDialog = new askText(this);
        askTextDialog->textToSet = &text;
        askTextDialog->setTittle("Name for the new session");
        int code = askTextDialog->exec();
        if(code != QDialog::Accepted) {
            return void();
        }
        qDebug() << "Received code in askText for ereader:" << text;
    }

    if (continueCreating == false || text.isEmpty() == true) {
        qWarning() << "No session text provided";
        returnToStart();
        return void();
    }

    qDebug() << "Selected session name:" << text;

    if(QFile(directories::sessionSaves.filePath(text)).exists() == true) {
        qWarning() << "Session of such name already exists";
        returnToStart();
        return void();
    }

    QSettings settings(directories::sessionSaves.filePath(text), QSettings::IniFormat);

    sessionStr newSession = sessionStr();
    newSession.core.deckPathList = deckPathList;
    newSession.core.mode = mode;
    newSession.core.name = text;

    qDebug() << "New Session:" << newSession;

    // Saving whole struct
    QVariant toSave = QVariant::fromValue(newSession);
    qDebug() << "toSave valid:" << toSave.isValid();

    settings.setValue("session", toSave);

    settings.sync();

    qDebug() << "Settings status:" << settings.status();

    qDebug() << "Saved settings at:" << settings.fileName();

    showSessions();
}

void MainWindow::statusBarPlayAdd() {
    resetStatusBar();

    statusBarCWidget->OptionButtonSet("Statistics", QIcon(":/icons/statistics.svg"), true);
    statusBarCWidget->OptionButtonSet2("", QIcon(), false);
    connect(statusBarCWidget, &statusBarC::optionButtonSignal, playDeck, &DeckPlay::showStats);

    statusBarCWidget->OptionButtonExit(QIcon(":/icons/back.svg"), true);
    connect(statusBarCWidget, &statusBarC::closeButtonSignal, this, &MainWindow::hardResetDeckPlay);

    // Reload font
    connect(statusBarCWidget, &statusBarC::closedOptionsDialog, playDeck, &DeckPlay::reloadSettings);
    // Set status
    connect(playDeck, &DeckPlay::changeStatusBarTextSignal, statusBarCWidget, &statusBarC::setStatusText);
}

void MainWindow::playSession(sessionStr sessionPlay) {
    qDebug() << "Playing session";

    // Status bar
    statusBarPlayAdd();

    grid->reset();
    grid->hide();

    // To make it calculate document size VERY IMPORTANT https://stackoverflow.com/questions/22457332/why-does-qtextedit-have-sometimes-document-height-0
    // It first needs to be shown, then calculate things!
    playDeck->show();
    playDeck->start(sessionPlay);
    areDecksShown = false;
}

void MainWindow::hardResetDeckPlay() {
    playDeck->exitIt();
    delete playDeck;
    playDeck = new DeckPlay(this);
    ui->gridMain->addWidget(playDeck);
    playDeck->hide();

    grid->show();
    showSessions();
}

// Settings need it
void MainWindow::updateGrid() {
    // Only when deck are shown
    if(areDecksShown == true) {
        showDecks();
    }
}
