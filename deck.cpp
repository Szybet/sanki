#include "deck.h"
#include "ui_deck.h"
#include "edit_deck.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <QWidget>
#include <QDebug>

deck::deck(QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::MainQwidget)
{
    ui->setupUi(this);
}

void deck::set_deck_name(QString text)
{
    ui->DeckNamePlayButton->setText(text);
}

void deck::refresh_decks_slot()
{
    qDebug() << "UPDATE - deck signal";
    emit refresh_decks_signal();
}

void deck::on_EditDeckbutton_clicked()
{
    edit_deck* edit_widget = new edit_deck();
    edit_widget->deck_info = deck_info;
    edit_widget->update_widget();
    edit_widget->show();
    connect(edit_widget, SIGNAL(refresh_decks_edit_signal()), this, SLOT(refresh_decks_slot()));
}

