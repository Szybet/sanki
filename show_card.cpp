#include "show_card.h"
#include "ui_show_card.h"

show_card::show_card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show_card)
{
    ui->setupUi(this);
}

show_card::~show_card()
{
    delete ui;
}
