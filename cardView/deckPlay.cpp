#include "cardView/deckPlay.h"
#include "qglobal.h"
#include "ui_deckPlay.h"
#include "global.h"
#include "cardView/modes/completlyRandom.h"
#include "cardView/modes/randomNoRepeat.h"
#include "cardView/functions/helperFunctions.h"
#include "components/other/statistics.h"
#include "cardView/modes/boxes/boxes.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QScrollBar>
#include <QTimer>
#include <QElapsedTimer>

#include <algorithm>
#include <random>

#ifdef EREADER
#include "einkenums.h"
#include "koboplatformfunctions.h"
#endif

DeckPlay::DeckPlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeckPlay)
{
    ui->setupUi(this);

    if(ereader) {
        // This could be editable in settings
        ui->scrollArea->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 50px; }");

        // This could be editable in settings
        ui->horizontalScrollBar->setStyleSheet("QScrollBar:horizontal { height: 50px; }");
    }

    ui->horizontalScrollBar->setHidden(true);
}

DeckPlay::~DeckPlay()
{
    delete ui;
}

void DeckPlay::start(sessionStr newSession)
{
    currectSession = newSession;        
    uint count = 0;
    foreach(QString dir, currectSession.core.deckPathList) {
        qDebug() << "deck path in session:" << dir;
        // http://katecpp.github.io/sqlite-with-qt/
        // Important: Connection as number
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString::number(count));

        QString databaseFile = findDatabaseFile(directories::deckStorage.filePath(dir));
        if(databaseFile == "none") {
            working = false;
            return void();
        }
        db.setDatabaseName(databaseFile);
        if (db.open() == true) {
            qDebug() << "Test open succesfull";
            realSqlDatabases.append(db);
        } else {
            qWarning() << "Failed to open database:" << dir;
            working = false;
            db.close();
            return void();
        }
        count = count + 1;
    }

    qDebug() << "realSqlDatabases:" << realSqlDatabases;

    if(currectSession.cardList.isEmpty()) {
        qDebug() << "Detected first time session load, adding cards";
        QString selectCardIds = "SELECT id FROM notes ORDER BY RANDOM()";
        for(int i = 0; i < realSqlDatabases.count(); i++) {
            qDebug() << "Getting id's for database:" << realSqlDatabases[i].databaseName();
            QSqlQuery idsQuery = realSqlDatabases[i].exec(selectCardIds);
            while(idsQuery.next()) {
                qDebug() << idsQuery.value(0);
                card newCard { idsQuery.value(0).toULongLong(), static_cast<uint>(i), 0, 0, 0, 0, 0 };
                currectSession.cardList.push_back(newCard);
            }
        }
        qDebug() << "Finished initializing cards:" << currectSession;

        // https://www.qtcentre.org/threads/55246-Randomization-QList-lt-QString-gt-on-label
        std::random_device rd;
        std::mt19937 rng(rd());

        ::std::shuffle(currectSession.cardList.begin(), currectSession.cardList.end(), rng);

        qDebug() << "Finished shuffling cards:" << currectSession.cardList;
    }

    saveSession = new QSettings(directories::sessionSaves.filePath(currectSession.core.name), QSettings::IniFormat);
    saveSession->setParent(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DeckPlay::saveSessionData);
    timer->setInterval(120000);
    timer->start();

    elapsedTimer = new QElapsedTimer;
    elapsedTimer->start();

    saveSessionData();

    if(currectSession.core.mode == CompletlyRandomised) {
        CompletlyRandom* mode = new CompletlyRandom(this);
        mode->setup(this, ui);
    } else if (currectSession.core.mode == Boxes) {
        boxes* mode = new boxes(this);
        connect(this, &DeckPlay::saveData, mode, &boxes::saveBox);
        mode->setup(this, ui);
    }

    reloadSettings();
}

void DeckPlay::cardSizeManage(QTextBrowser *text) {
    QApplication::processEvents();
    int height = text->document()->size().height();
    QString objectName = text->objectName();
    QScrollBar* scrollbar = ui->horizontalScrollBar;
    qDebug() << "Document height:" << height << "and sizeHint:" << ui->textFrontCard->sizeHint().height() << "for" << objectName;
    if(height != 0 && text->isHidden() == false) {
        qDebug() << "Setting" << text->objectName() << "height";
        text->setFixedHeight(height);

        int documentWidth = text->document()->size().width();
        int textWidth = text->size().width();
        qDebug() << "documentWidth:" << documentWidth << "textWidth:" << textWidth;
        if (documentWidth > textWidth) {
            qDebug() << "So a scroll bar could be needed";
            if(objectName == "textBackCard") {
               qDebug() << "Enabled manageBackScrollBar";
               manageBackScrollBar = true;
            } else if(objectName == "textFrontCard" ) {
               qDebug() << "Enabled manageFrontScrollBar";
               manageFrontScrollBar = true;
            }

            QApplication::processEvents();
            // WHY does it need to be like that, otherwise pagestep is too small at start...
            QTimer::singleShot(0, this, [this, scrollbar, text]() {
                scrollBarClone(scrollbar, text);
            });
        } else {
            // Disable if not needed
            if(objectName == "textBackCard") {
               qDebug() << "Enabled manageBackScrollBar";
               manageBackScrollBar = false;
            } else if(objectName == "textFrontCard" ) {
               qDebug() << "Enabled manageFrontScrollBar";
               manageFrontScrollBar = false;
            }
        }

        if((manageBackScrollBar == true || manageFrontScrollBar == true) && scrollbar->isHidden() == true) {
            scrollbar->setHidden(false);
        } else if(manageBackScrollBar == false && manageFrontScrollBar == false && scrollbar->isHidden() == false) {
            scrollbar->setHidden(true);
        }
    }
}

// Should be called after next card is called, but before the front is set
void DeckPlay::resetScrollState() {
    manageBackScrollBar = false;
    manageFrontScrollBar = false;
}


void DeckPlay::on_horizontalScrollBar_valueChanged(int value)
{
    // qDebug() << "Main horizontal scroll bar value:" << value;
    if(manageFrontScrollBar == true) {
        ui->textFrontCard->horizontalScrollBar()->setValue(value);
    }
    if(manageBackScrollBar == true) {
        ui->textBackCard->horizontalScrollBar()->setValue(value);
    }
}

void DeckPlay::scrollBarClone(QScrollBar* scrollbar, QTextBrowser* text) {
    int maximumMainScrollBar = scrollbar->maximum();
    int maximumCardScrollBar = text->horizontalScrollBar()->maximum();
    dumpScrollBarInfo(scrollbar);
    dumpScrollBarInfo(text->horizontalScrollBar());
    // Checks if both are enabled - if not, it sets the maximum to the same value - if yes, it checks if the maximum is already above the value - if it's not it sets this value, if it is it ignores
    if(manageBackScrollBar == true && manageFrontScrollBar == true) {
        if(maximumMainScrollBar < maximumCardScrollBar) {
            scrollbar->setMaximum(maximumCardScrollBar);
        }
    } else {
        scrollbar->setMaximum(maximumCardScrollBar);
    }
    // Set other thing
    QApplication::processEvents();
    int pageStep = text->horizontalScrollBar()->pageStep();
    scrollbar->setPageStep(pageStep);
    int singleStep =  text->horizontalScrollBar()->singleStep();
    scrollbar->setSingleStep(singleStep);

    // Move it back
    scrollbar->setValue(0);
    text->horizontalScrollBar()->setValue(0);

    dumpScrollBarInfo(scrollbar);
    dumpScrollBarInfo(text->horizontalScrollBar());
}

void DeckPlay::setText(QTextBrowser* area, QString text) {
    area->setHtml(text);

    // Very important
    area->document()->adjustSize();

    centerText(area);

    cardSizeManage(area);

    if(firstLaunch == true) {
        // TODO: at launch frontcard is too big
    }

    // This fixes the issue that after adding text it is cutted in half
    // Doesn't work ui->textFrontCard->verticalScrollBar()->setSliderPosition(0);
    area->verticalScrollBar()->setValue(0);
}

void DeckPlay::saveSessionData() {
    if(working == false) {
        return void();
    }
    qint64 timerElapsed = elapsedTimer->restart();
    if(timerElapsed > 120000 && already2Minutes == false) {
        currectSession.time.playedCount += 1;
        already2Minutes = true;
    }

    emit saveData();
    QApplication::processEvents();

    qDebug() << "Time for elapsedTimer when saving:" << timerElapsed << "and currectSession.time.played:" << currectSession.time.played;

    currectSession.time.lastUsed = QDateTime::currentDateTime();
    currectSession.time.played += timerElapsed;

    QVariant variant = QVariant::fromValue(currectSession);

    qDebug() << "Variant:" << variant;

    if(saveSession->isWritable() && variant.isValid()) {
        saveSession->setValue("session", variant);
        saveSession->sync();
        qDebug() << "Saved session";
    } else {
        qWarning() << "Failed to save session";
    }
}

void DeckPlay::exitIt() {
    qDebug() << "Exit it DeckPlay called";
    if(working == false) {
        return void();
    }
    saveSessionData();
    timer->stop();
    timer->disconnect();
    elapsedTimer->invalidate();
    delete elapsedTimer;
    qDebug() << "Count of connections:" << realSqlDatabases.count();
    // Is there a cleaner way?
    warningsEnabled = false;
    for(int i = 0; i < realSqlDatabases.count(); i++) {
        realSqlDatabases[i].close();
        QSqlDatabase::removeDatabase(QString::number(i));
    }
    warningsEnabled = true;
}

void DeckPlay::showStats() {
    qDebug() << "showStats";
    // Avoid crashes
    if(working == false) {
        return void();
    }
    saveSessionData();
    statistics* newStats = new statistics(this);
    if(ereader) {
        newStats->show(); // I said before but calculate things important etc;
    }
    newStats->start(currectSession);
    newStats->exec();
    // Important - eink change
    reloadSettings();
}

void DeckPlay::reloadSettings() {
    qDebug() << "Reload settings called";

    QSettings settingsGlobal(directories::globalSettings.fileName(), QSettings::IniFormat);
    QVariant variant = settingsGlobal.value("playFont");
    QFont font = variant.value<QFont>();

    ui->textBackCard->setFont(font);
    ui->textFrontCard->setFont(font);

#ifdef EREADER
    // To flush settings window...
    KoboPlatformFunctions::setFullScreenRefreshMode(WaveForm_GC16);
    QApplication::processEvents();
    KoboPlatformFunctions::doManualRefresh(QRect(0, 0, ereaderVars::screenX, ereaderVars::screenY));
    KoboPlatformFunctions::doManualRefresh(QRect(0, 0, ereaderVars::screenX, ereaderVars::screenY));
    QApplication::processEvents();
#endif

#ifdef EREADER
    int waveform = settingsGlobal.value("deckPlayWaveForm").toInt();
    qDebug() << "Setting waveform mode for deckPlay:" << waveform;
    // Does this work?
    WaveForm waveformBetter = static_cast<WaveForm>(waveform);
    KoboPlatformFunctions::setFullScreenRefreshMode(waveformBetter);
#endif
    this->repaint();
    this->repaint();
    this->repaint();
}

void DeckPlay::changeStatusBarTextSlot(QString text) {
    emit changeStatusBarTextSignal(text);
}
