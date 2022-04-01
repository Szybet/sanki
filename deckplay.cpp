#include "deckplay.h"
#include "ui_deckplay.h"

#include <QDebug>

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

void DeckPlay::provide_deck(QDir dir)
{
    deck_dir = dir;
}

void DeckPlay::start()
{
    qDebug() << "deckplaystart";
}
