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
    show_card* show_card_widget = new show_card;
    ui->gridManageCard->addWidget(show_card_widget);
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
    QString front_card = front_query.value(0).toString();
    qDebug() << "Database front_card" << front_card;

    QSqlQuery back_query = db.exec(back_std_sql);
    back_query.next();
    QString back_card = back_query.value(0).toString();
    qDebug() << "Database back_card" << back_card;
    // On the back is this:
    // front_card + this character https://unicode-table.com/en/001F/
    // and then the important rest

}
