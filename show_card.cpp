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

void show_card::on_pushButton_clicked()
{
    emit clicked();
}

void show_card::set_text(QString text)
{
    ui->pushButton->setText(text);
}
