#include "cardView/deckPlay.h"
#include "ui_deckPlay.h"
#include "cardView/showCard.h"
#include "globals.h"
#include "cardView/modes/completlyRandom.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QScrollBar>
#include <QTimer>

/*
 * Note about scroll bars: Qt is so buggy with those, there were needed many workaround and hacks... its a mess
*/

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
               modeRandomNoRepeatSetup();
           }
        }
        else
        {
           qDebug() << "Database: connection with database failed";
        }
    }
    else
    {
        qDebug() << "Database: doesn't exist";
    }
}

void DeckPlay::modeRandomNoRepeatSetup()
{

    // Setup show / next card button
    showCard* showCardWidget = new showCard;
    connect(showCardWidget, SIGNAL(clicked()), this, SLOT(showBackCard())); // Button slot
    connect(this, SIGNAL(setButtonText(QString)), showCardWidget, SLOT(setText(QString)));
    connect(this, SIGNAL(nextCardCall()), this, SLOT(modeRandomNoRepeatLoop())); // a loop it is 1
    ui->gridManageCard->addWidget(showCardWidget);

    QSqlQuery query_count = db.exec("SELECT COUNT(id) FROM notes as whatthefuck");
    query_count.next();
    no_repeat_list = query_count.value(0).toInt();

    qDebug() << "column in notes: " << no_repeat_list;

    modeRandomNoRepeatLoop();
}

void DeckPlay::modeRandomNoRepeatLoop()
{
    /*
    if(no_repeat_ids.count() == no_repeat_list)
    {
        int remove_first = no_repeat_ids.count() - (no_repeat_ids.count() / 3);
        if(remove_first == 0)
        {
            // shouldnt happen
            no_repeat_ids.clear();
        }
        for(int i = 0; i <= remove_first; ++i)
        {
            no_repeat_ids.removeFirst();
        }
    }

    bool looping = true;
    QString id_str;
    while(looping == true)
    {
        QSqlQuery query_id = db.exec("SELECT id FROM notes ORDER BY RANDOM() LIMIT 1");
        query_id.next();
        QString id_str_unchecked = query_id.value(0).toString(); // random id
        if(no_repeat_ids.contains(id_str_unchecked) == false)
        {
            id_str = id_str_unchecked;
            no_repeat_ids.append(id_str_unchecked);
            looping = false;
        }
    }

    // set variables
    QString mainCardSql = "SELECT flds FROM notes WHERE id=" + id_str;

    QSqlQuery MainCardQuery = db.exec(mainCardSql);
    MainCardQuery.next();
    mainCard = MainCardQuery.value(0).toString();

    // Parse the text
    correctString();

    ui->textFrontCard->setText(frontCard);
    // This fixes the issue with not showing the first line. it simply moved the scrollbar a bit and there were problems. the scrollbar was hided
    ui->textFrontCard->verticalScrollBar()->setValue(0);

    // Some magic: at the launch it shows height 0, and with this it is a bit bigger. not an ideal solution
    if(firstLaunch == true)
    {
        firstLaunch = false;
        //mode_crandom_loop();
    }

    // This isEmpty() needs to be done after setText becouse it will Segment fault
    if(ui->textFrontCard->document()->isEmpty() == false)
    {
        ui->textFrontCard->selectAll();
        ui->textFrontCard->setAlignment(Qt::AlignCenter);

        // This removes selection
        QTextCursor cursor = ui->textFrontCard->textCursor();
        cursor.clearSelection();
        ui->textFrontCard->setTextCursor(cursor);
    }

    // This fixes the issue with not showing the first line. it simply moved the scrollbar a bit and there were problems. the scrollbar was hided
    // this needs to be here too...
    ui->textFrontCard->verticalScrollBar()->setValue(0);
*/
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
    mainCard->append("<br>");
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
