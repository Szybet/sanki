#include "deck.h"
#include "ui_deck.h"

#include <QMainWindow>
#include <QWidget>


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
