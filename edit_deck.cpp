#include "edit_deck.h"
#include "ui_edit_deck.h"
#include "mainwindow.h"

#include <QDebug>

edit_deck::edit_deck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_deck)
{
    ui->setupUi(this);
}

edit_deck::~edit_deck()
{
    //delete ui;
}

void edit_deck::update_widget()
{
    QString deck_name = deck_info.baseName();
    ui->textEditDeckName->setPlainText(deck_name);
}

void edit_deck::on_ButtonRemoveDeck_clicked()
{
    remove_deck = true;
}


void edit_deck::on_ButtonReset_clicked()
{
    reset_deck = true;
}


void edit_deck::on_textEditDeckName_textChanged()
{
    updated_name = ui->textEditDeckName->toPlainText();
}

void edit_deck::on_ButtonCancelEdit_clicked()
{
    emit refresh_decks_edit_signal();
    edit_deck::close();
}


void edit_deck::on_ButtonSaveExit_clicked()
{
    QDir dir = deck_info.dir();
    if (updated_name != "")
    {
        dir.QDir::rename(deck_info.baseName(), updated_name);
    }
     qDebug() << "GOING REMOVED";
    if (remove_deck == true)
    {
        if (updated_name == deck_info.baseName())
        {

            QDir deck_dir = deck_info.path() + "/" + deck_info.baseName();
            qDebug() << "REMOVED PATH" << deck_dir;
            qDebug() << "REMOVED";
            deck_dir.removeRecursively();
        } else {
            qDebug() << "NOT REMOVED";
        }
    }
    if (reset_deck == true)
    {
        // Reset the sql database in the future
    }

    // Update decks

    //MainWindow m(this);
    //emit m.remove_decks();
    //m.update_decks();

    emit refresh_decks_edit_signal();
    edit_deck::close();



}

