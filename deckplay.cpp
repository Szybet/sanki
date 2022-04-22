#include "deckplay.h"
#include "ui_deckplay.h"
#include "show_card.h"

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
    show_card* show_card_widget = new show_card;
    connect(show_card_widget, SIGNAL(clicked()), this, SLOT(show_back_next()));
    connect(this, SIGNAL(show_button_text(QString)), show_card_widget, SLOT(set_text(QString))); // It works, but there is no color
    ui->gridManageCard->addWidget(show_card_widget);


}

DeckPlay::~DeckPlay()
{
    delete ui;
}

void DeckPlay::update(QDir dir, int mode_new)
{
    deck_dir = dir;
    mode = mode_new;
    qDebug() << "DECKPLAY - UPDATE" << dir << "int is:" << mode_new;
    start();
}

void DeckPlay::start()
{
    db_path_str = deck_dir.path() + "/collection.anki2";
    QFile db_path{db_path_str};

    if (db_path.exists() == true)
    {
        qDebug() << "SQLITE DATABSE OPEN";
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(db_path_str);
        // http://katecpp.github.io/sqlite-with-qt/

        if (db.open() == true)
        {
           // Everything is good, start making the GUI
           next_card();

           /* example
           qDebug() << "Database: connection ok";
           QSqlQuery query("SELECT id FROM notes");
               while (query.next()) {
                   QString country = query.value(0).toString();
                   qDebug() << "Database" << country;
               }
           */

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

void DeckPlay::next_card()
{
    QSqlQuery query_id = db.exec("SELECT id FROM notes ORDER BY RANDOM() LIMIT 1");
    // int id = query.value(1).toInt();
    query_id.next();
    // its too big fir int
    QString id_str = query_id.value(0).toString();
    qDebug() << "Database random id_str" << id_str;
    QString front_std_sql = "SELECT sfld FROM notes WHERE id=" + id_str;
    QString back_std_sql = "SELECT flds FROM notes WHERE id=" + id_str;

    QSqlQuery front_query = db.exec(front_std_sql);
    front_query.next();
    front_card = front_query.value(0).toString();
    qDebug() << "Database front_card" << front_card;

    QSqlQuery back_query = db.exec(back_std_sql);
    back_query.next();
    back_card = back_query.value(0).toString();
    qDebug() << "Database back_card" << back_card;
    // On the back is this:
    // front_card + this character https://unicode-table.com/en/001F/
    // and then the important rest

    ui->textFrontCard->setText(front_card);

}

void DeckPlay::show_back_next()
{
    qDebug() << "play_deck show_back" << back_card;
    if (showed_back == false)
    {
        showed_back = true;
        int char_to_remove = front_card.count() + 1;
        QString new_back = back_card.remove(0, char_to_remove);
        qDebug() << "play_deck better_back" << new_back;
        ui->textBackCard->setText(new_back);
        emit show_button_text("Next Card");
    }
    else
    {
        showed_back = false;
        emit show_button_text("Show");
        ui->textBackCard->setText("");
        next_card();

    }

}
