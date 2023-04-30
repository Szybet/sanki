#include "cardView/deckPlay.h"
#include "ui_deckPlay.h"
#include "global.h"
#include "cardView/modes/completlyRandom.h"
#include "cardView/modes/randomNoRepeat.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QScrollBar>
#include <QTimer>

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

void DeckPlay::update(QDir dir, DeckModes modeNew)
{
    // This is just providing values and then updating
    deckDir = dir;
    mode = modeNew;

    mediaFile.setFileName(deckDir.path() + QDir::separator() + "media");

    qDebug() << "media file is: " << mediaFile.fileName();
    if (mediaFile.exists()) {
        qDebug() << "media file exists";
    } else {
        qDebug() << "media file does not exist";
    }

    QStringList StringListSearchPaths = {deckDir.path()};

    // Important
    ui->textBackCard->setSearchPaths(StringListSearchPaths);
    ui->textFrontCard->setSearchPaths(StringListSearchPaths);

    start();
}

void DeckPlay::start()
{
    // Support for this newer anki database... why did they break it
    QFile collection21 = deckDir.path() + QDir::separator() + "collection.anki21";
    QFile collection2 = deckDir.path() + QDir::separator() + "collection.anki2";
    QFile* dbPath = nullptr;

    if(collection21.exists() == true)
    {
        dbPath = &collection21;
    } else if(collection2.exists() == true) {
        dbPath = &collection2;
        qCritical() << "Only old version of the database was found, propably this will cause problems";
    } else {
        qFatal("No supported collection file found in this deck. It's propably too new, and hasn't been tested");
    }

    if (dbPath->exists() == true)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath->fileName());
        // http://katecpp.github.io/sqlite-with-qt/

        if (db.open() == true)
        {
           // Everything is good, start making the GUI, check mode
           if(mode == CompletlyRandomised) // Completly random
           {
               CompletlyRandom* mode = new CompletlyRandom(this);
               mode->setup(this, ui, &db);
           }else if(mode == RandomisedNoRepeating) // Random - no repeat
           {
               randomNoRepeat* mode = new randomNoRepeat(this);
               mode->setup(this, ui, &db);
           }
        }
        else
        {
           qFatal("Database: connection with database failed");
        }
    }
    else
    {
        qFatal("Database: doesn't exist");
    }
}

void DeckPlay::correctString(QString* mainCard)
{
    // turn those weird image id's to file names
    // this is a json file, but a weird one so...
    // TODO: In the future this needs to be done using json parsing.
    if(mainCard->contains("<img src="))
    {
        mediaFile.open(QIODevice::ReadOnly);
        QString media_contend = mediaFile.readAll();
        mediaFile.close();

        media_contend = media_contend.replace("{", "");
        media_contend = media_contend.replace("}", "");

        // This is impossible becouse of:  "7": "rew-zasada lewej 1.png"
        // media_contend = media_contend.replace(" ", "");
        // for now this:
        media_contend = media_contend.replace(": ", ":");
        media_contend = media_contend.replace(", ", ",");

        QStringList split_dot = media_contend.split(",");
        for(const QString &item: split_dot)
        {
            media_contend = media_contend.replace("\"", "");

            qDebug() << "item is: " << item;

            QStringList replace_items = item.split(":");
            if(mainCard->contains(replace_items.last()))
            {
               qDebug() << "mainCard contains items_last";
               mainCard = &mainCard->replace(replace_items.last(), replace_items.first());
            }
        }
    }

    // Weird: &nbsp; ( hard space in html ) sometimes doesn't get parsed
    mainCard = &mainCard->replace("&nbsp;", " ");

    // Add a line at the end becouse one line is cutted out...
    // mainCard->append("<br>");
    // On reader fixed cutted off line
    // Causes problem with scroll appearing
}

void DeckPlay::splitMainCard(QString mainCard, QString* frontCard, QString* backCard) {
    // mainCard is:
    // frontCard + this character https://unicode-table.com/en/001F/ + backCard
    QStringList cards = mainCard.split("\u001F");
    qDebug() << "cards splitted are: " << cards;

    *frontCard = cards.first();
    *backCard = cards.last();

    qDebug() << "frontCard is: " << *frontCard;
    qDebug() << "backCard is: " << *backCard;
}

void DeckPlay::centerText(QTextBrowser* text) {
    // This isEmpty() needs to be done after setText becouse it will Segment fault
    if(text->document()->isEmpty() == false)
    {
        text->selectAll();
        text->setAlignment(Qt::AlignCenter);

        // This removes selection
        QTextCursor cursor = text->textCursor();
        cursor.clearSelection();
        text->setTextCursor(cursor);
    }
}

void DeckPlay::cardSizeManage(QTextBrowser *text) {
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

void DeckPlay::dumpScrollBarInfo(QScrollBar* scroll) {
    if (scroll) {
        /*
        qDebug() << "ScrollBar - Object Name: " << scroll->objectName()
                 << ", Minimum value: " << scroll->minimum()
                 << ", Maximum value: " << scroll->maximum()
                 << ", Page step: " << scroll->pageStep()
                 << ", Single step: " << scroll->singleStep()
                 << ", Value: " << scroll->value()
                 << ", Slider position: " << scroll->sliderPosition();
        */
    } else {
        qDebug() << "ScrollBar - Object Name: NULL";
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
