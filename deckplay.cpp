#include "deckplay.h"
#include "ui_deckplay.h"

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
