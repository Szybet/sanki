#include "card_true_false.h"
#include "ui_card_true_false.h"

card_true_false::card_true_false(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::card_true_false)
{
    ui->setupUi(this);
}

card_true_false::~card_true_false()
{
    delete ui;
}
