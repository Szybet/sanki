#include "card_view/deckplay.h"
#include "ui_deckplay.h"
#include "card_view/show_card.h"
#include "globals.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>

DeckPlay::DeckPlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeckPlay)
{
    ui->setupUi(this);

}

DeckPlay::~DeckPlay()
{
    delete ui;
}

void DeckPlay::update(QDir dir, int mode_new)
{
    // This is just provifing values and then updating
    deck_dir = dir;
    mode = mode_new;

    //media_file = QFile{deck_dir.path() + "/media"};
    media_file.setFileName(deck_dir.path() + "/media");

    QString message = "media file is: ";
    message.append(media_file.fileName());
    global_fun::log(message, log_file, "update");
    if(media_file.exists() == true)
    {
        global_fun::log("media file exists", log_file, "update");
    } else {
        global_fun::log("media file does not exists", log_file, "update");
    }

    QStringList string_list = {deck_dir.path()};
    ui->textBackCard->setSearchPaths(string_list);

    start();
}

void DeckPlay::start()
{
    db_path_str = deck_dir.path() + "/collection.anki2";
    QFile db_path{db_path_str};

    if (db_path.exists() == true)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(db_path_str);
        // http://katecpp.github.io/sqlite-with-qt/

        if (db.open() == true)
        {
           // Everything is good, start making the GUI, check mode
           if(mode == 1) // Completly random
           {
               mode_crandom_setup();
           }
        }
        else
        {
           global_fun::log("Database: connection with database failed", log_file, "start");
        }
    }
    else
    {
        global_fun::log("Database: doesn't exist", log_file, "start");
    }
}

void DeckPlay::mode_crandom_setup()
{
    // Setup show / next card button
    show_card* show_card_widget = new show_card;
    connect(show_card_widget, SIGNAL(clicked()), this, SLOT(show_back_next())); // Button slot
    connect(this, SIGNAL(show_button_text(QString)), show_card_widget, SLOT(set_text(QString)));
    connect(this, SIGNAL(next_card_call()), this, SLOT(mode_crandom_loop())); // a loop it is 1
    ui->gridManageCard->addWidget(show_card_widget);

    // a loop it is 2
    mode_crandom_loop();
}

void DeckPlay::mode_crandom_loop()
{
    QSqlQuery query_id = db.exec("SELECT id FROM notes ORDER BY RANDOM() LIMIT 1");
    query_id.next();
    // its too big for int
    QString id_str = query_id.value(0).toString(); // random id

    // set variables
    QString main_std_sql = "SELECT flds FROM notes WHERE id=" + id_str;

    QSqlQuery main_query = db.exec(main_std_sql);
    main_query.next();
    main_card = main_query.value(0).toString();

    // Parse the text
    parse_string();

    ui->textFrontCard->setText(front_card);
}

void DeckPlay::show_back_next()
{
    if (showed_back == false)
    {
        showed_back = true;
        ui->textBackCard->setText(back_card);
        emit show_button_text("Next Card");
    }
    else
    {
        showed_back = false;
        emit show_button_text("Show");
        ui->textBackCard->setText("");

        emit next_card_call();
    }

}

void DeckPlay::parse_string()
{
    // turn those weird image id's to file names
    // this is a json file, but a weird one so...
    if(main_card.contains("<img src="))
    {
        media_file.open(QIODevice::ReadOnly);
        QString media_contend = media_file.readAll();
        media_file.close();

        media_contend = media_contend.replace("{", "");
        media_contend = media_contend.replace("}", "");
        media_contend = media_contend.replace(" ", "");

        QStringList split_dot = media_contend.split(",");
        for(QString item: split_dot)
        {
            media_contend = media_contend.replace("\"", "");

            QString message4 = "item is: ";
            message4.append(item);
            global_fun::log(message4, log_file, "media_contend");

            QStringList replace_items = item.split(":");
            if(main_card.contains(replace_items.last()))
            {
                global_fun::log("main_card contains items_last", log_file, "media_contend");
                main_card = main_card.replace(replace_items.last(), replace_items.first());
            }
        }
    }



    // main_all is:
    // front_card + this character https://unicode-table.com/en/001F/ + back_card
    QStringList cards = main_card.split("\u001F");
    QString message3 = "cards splitted are: ";
    for(QString card: cards)
    {
        message3.append(card);
        message3.append(",");
    }
    global_fun::log(message3, log_file, "parse_string");

    front_card = cards.first();
    back_card = cards.last();


    QString message2 = "front_card is: ";
    message2.append(front_card);
    global_fun::log(message2, log_file, "parse_string");

    QString message = "back_card is: ";
    message.append(back_card);
    global_fun::log(message, log_file, "parse_string");

}
