#include "mainMenu/mainWindow.h"
#include "cardView/deckPlay.h"
#include "mainMenu/decks/deck.cpp"
#include "ui_mainWindow.h"
#include "components/statusBarC.h"
#include "mainMenu/fancyGrid.h"
#include "global.h"
#include "cardView/modeChooser.h"
#include "zip.h"
#include "components/files/fileChooser.h"

#include <QTime>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QInputDialog>

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

    showSessions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGrid() {
    emit killItems();
    grid->disconnect();
    grid->reset();
}

void MainWindow::resetStatusBar() {
    statusBarCWidget->disconnect();
}

void MainWindow::deckPlayStart(QDir dir)
{
    /*
    // This here goes to cardView thing, going to play
    qDebug() << "Dir choosed to play:" << dir.path();

    // this was propably causing problems
    //int mode = chooseMode->exec();

    modeChooser* chooseMode = new modeChooser;
    connect(chooseMode, SIGNAL(setMode(DeckModes)), this, SLOT(getMode(DeckModes)));
    int code = chooseMode->exec();
    qDebug() << "chooseMode dialog return value is:" << code;
    if(code == QDialog::Accepted) {
        // status bar for this
        emit close_statusBarC();
        statusBarC* statusBarC_up = new statusBarC();
        statusBarC_up->optionButtonSet(false); // WARNING NDUASNDJK
        connect(this, SIGNAL(close_statusBarC()), statusBarC_up, SLOT(close()));
        connect(statusBarC_up, SIGNAL(closeButtonSignal()), this, SLOT(returnToStart()));
        ui->gridStatus->addWidget(statusBarC_up);

        emit clear_mainwidget();
        QLayout* central_layout = ui->centralwidget->layout();
        DeckPlay* playDeck = new DeckPlay();
        playDeck->update(dir, mode);
        connect(this, SIGNAL(clear_mainwidget()), playDeck, SLOT(close()));
        central_layout->addWidget(playDeck);
    }
    */
}

void MainWindow::showSessions() {
    statusBarSessionAdd();

    resetGrid();

    connect(grid, &fancyGrid::addItem, this, &MainWindow::addSlotSession);

    foreach(QString file , directories::sessionSaves.entryList(QDir::NoDotAndDotDot | QDir::Files)) {
        qDebug() << "Session file:" << file;
    }

    grid->show();
}

void MainWindow::showDecks() {
    qDebug() << "Show decks called";
    deckPathList.clear();

    statusBarDeckAdd();

    resetGrid();

    connect(grid, &fancyGrid::addItem, this, &MainWindow::extractDeck);

    foreach(QString file , directories::deckStorage.entryList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        qDebug() << "Deck dir:" << file;
        deck* newDeck = new deck(this);

        connect(this, &MainWindow::killItems, newDeck, &deck::close);
        connect(newDeck, &deck::selectedDeck, this, &MainWindow::getDeck);
        newDeck->start(file);

        grid->addWidget(newDeck);
    }
    grid->show();
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
        fileChooserCustomDialog->start_path = directories::deckSelect.path();
        fileChooserCustomDialog->update_files();
        connect(fileChooserCustomDialog, &fileChooserCustom::provideFile, this, &MainWindow::getFile);
        fileChooserCustomDialog->exec();
    } else if(pc) {
        zipFilePath = QFileDialog::getOpenFileName(this, "Select anki deck", directories::deckSelect.path(), "Anki Files (*.zip *.apkg)");
    }

    QFile zipFile{zipFilePath};
    if (zipFile.exists()) {
        qDebug() << "zip to be added exists";

        QDir newDeck;
        QFileInfo zipFile_info(zipFilePath);
        newDeck.setPath(directories::deckStorage.path() + QDir::separator() + zipFile_info.baseName());

        qDebug() << "new deck path: " << newDeck.path();

        directories::deckStorage.mkdir(zipFile_info.baseName());

        // Converting to acceptable string
        QByteArray ba = zipFilePath.toLocal8Bit();
        const char *char_converted = zipFilePath.toLocal8Bit().data();
        int arg = 2; // why
        zip_extract(char_converted, newDeck.path().toLocal8Bit().data(), 0, &arg);
    }
    // Update decks
    qDebug() << "extractDeck emitted";
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
    connect(statusBarCWidget, &statusBarC::optionButtonSignal, this, &MainWindow::extractDeck);
    connect(statusBarCWidget, &statusBarC::closeButtonSignal, this, &MainWindow::close);
}

void MainWindow::statusBarDeckAdd() {
    resetStatusBar();

    statusBarCWidget->OptionButtonSet("Add deck", QIcon(":/icons/deckAdd.svg"), true);
    statusBarCWidget->OptionButtonSet2("Confirm", QIcon(":/icons/confirm.svg"), true);
    connect(statusBarCWidget, &statusBarC::optionButtonSignal, this, &MainWindow::extractDeck);
    connect(statusBarCWidget, &statusBarC::option2ButtonSignal, this, &MainWindow::doneSelectingDecks);
    connect(statusBarCWidget, &statusBarC::closeButtonSignal, this, &MainWindow::close);
}

void MainWindow::returnToStart()
{
    qDebug() << "help";
    showSessions();
    statusBarSessionAdd(); // todo
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
    createSession();
}

void MainWindow::createSession() {
    // Ask for name
    bool continueCreating = true;
    QString text;

    if(pc) {
        text = QInputDialog::getText(this, tr("Insert text"),
                                             tr("Provide name for session"), QLineEdit::Normal,
                                             "", &continueCreating);
    }
    if(ereader) {
        // TODO: use custom askText dialog
    }

    if (continueCreating == false || text.isEmpty() == true) {
        return void();
    }

    qDebug() << "Selected session name:" << text;
}
