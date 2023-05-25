#include "mainMenu/decks/deck.h"
#include "global.h"
#include "ui_deck.h"
#include "mainMenu/decks/editDeck.h"
#include "cardView/functions/helperFunctions.h"

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QAbstractTextDocumentLayout>
#include <QToolTip>

deck::deck(QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::MainQwidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->deck->setStyleSheet("font-size: 8pt");
    ui->ButtoneditDeck->setStyleSheet("font-size: 8pt");
    ui->LabelStats->setStyleSheet("font-size: 8pt");
    ui->ButtonfileSelect->setStyleSheet("font-size: 8pt");

}

void deck::start(QString path) {
    mainPath = path;
    name = path.split(QDir::separator()).last();
    ui->deck->setText(name);

    QString stats;

    QDir dir(mainPath);
    if(dir.exists() == false) {
        qWarning() << "Deck doesn't exists?" << path;
    }
    QFile fileAdded(dir.filePath(deckAddedFileName));

    qDebug() << "fileAdded:" << fileAdded << "exists:" << fileAdded.exists();

    if(fileAdded.exists()) {
        fileAdded.open(QIODevice::ReadOnly);
        QString date = fileAdded.readAll();
        fileAdded.close();
        stats = stats + "Added: " + date + "<br>";
    }

    QString databaseName = "cardCounter";
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", databaseName);
        db.setDatabaseName(findDatabaseFile(dir));
        if(db.open()) {
            QSqlQuery answer = db.exec("SELECT COUNT(id) FROM notes");
            answer.next();
            stats = stats + "Cards: " + answer.value(0).toString();
        }
        db.close();
    }
    QSqlDatabase::removeDatabase(databaseName);
    ui->LabelStats->setText(stats);
}

void deck::on_ButtoneditDeck_clicked()
{
    qDebug() << "Edit button clicked, editing deck: " << mainPath;
    editDeck* editWidget = new editDeck();
    connect(editWidget, &editDeck::refreshDecksSignal, this, &deck::refreshDecksSlot);
    editWidget->updateDeck(mainPath);
    editWidget->exec();
}

void deck::on_deck_selectionChanged()
{
    // This shows the full name when clicked
    ui->deck->setSelection(0, 0);
    QToolTip::showText( ui->deck->mapToGlobal( QPoint( 0, 0 ) ), mainPath.split(QDir::separator()).last() );
}

void deck::on_ButtonfileSelect_clicked()
{
    emit selectedDeck(mainPath);
}

void deck::refreshDecksSlot() {
    emit refreshDecks();
}
