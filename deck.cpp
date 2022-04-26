#include "deck.h"
#include "ui_deck.h"
#include "edit_deck.h"
#include "mainwindow.h"
#include "deckplay.h"
#include "globals.h"

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
    ui->deck->setStyleSheet("font-size: 8pt");
    ui->ButtonEditDeck->setStyleSheet("font-size: 8pt");
    ui->LabelStats->setStyleSheet("font-size: 8pt");
    ui->ButtonDeckPlay->setStyleSheet("font-size: 8pt");

}

void deck::set_deck_name(QString text)
{
    ui->deck->setText(text);
}

void deck::refresh_decks_slot()
{
    global_fun::log("Refresh decks slot received, emitting along", "deck.cpp", "refresh_decks_slot()");
    emit refresh_decks_signal();
}

void deck::on_ButtonEditDeck_clicked()
{
    QString message = "Edit button clicked, editing deck: ";
    message.append(deck_info.baseName());
    global_fun::log(message, "deck.cpp", "on_ButtonEditDeck_clicked()");

    edit_deck* edit_widget = new edit_deck();
    edit_widget->deck_info = deck_info;
    edit_widget->update_deck();

    connect(edit_widget, SIGNAL(refresh_decks_edit_signal()), this, SLOT(refresh_decks_slot()));
    edit_widget->exec();

}


void deck::on_ButtonDeckPlay_clicked()
{

    QDir deck_dir = deck_info.absoluteFilePath();
    qDebug() << "DECKPLAY - DECK";
    emit play_deck(deck_dir);
}

void deck::on_deck_selectionChanged()
{
    // This shows the full name when clicked
    ui->deck->setSelection(0, 0);
    QToolTip::showText( ui->deck->mapToGlobal( QPoint( 0, 0 ) ), deck_info.fileName() );
}

