#include "deckplay.h"
#include "ui_deckplay.h"

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
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName(deck_dir.path() + "/collection.anki2");
     // http://katecpp.github.io/sqlite-with-qt/

     // my god this will go true even if the database doesn't exist
     // ._ .
     if (db.open() == true)
     {
        qDebug() << "Database: connection ok";
        QSqlQuery query("SELECT id FROM notes");
            while (query.next()) {
                QString country = query.value(0).toString();
                qDebug() << "Database" << country;
            }

     }
     else
     {
        qDebug() << "Database: connection with database failed";
     }
}
