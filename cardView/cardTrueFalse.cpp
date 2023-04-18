#include "cardView/cardTrueFalse.h"
#include "ui_cardTrueFalse.h"

cardTrueFalse::cardTrueFalse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cardTrueFalse)
{
    ui->setupUi(this);
}

cardTrueFalse::~cardTrueFalse()
{
    delete ui;
}
