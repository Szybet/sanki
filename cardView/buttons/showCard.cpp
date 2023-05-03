#include "cardView/buttons/showCard.h"
#include "ui_showCard.h"

showCard::showCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showCard)
{
    ui->setupUi(this);
}

showCard::~showCard()
{
    delete ui;
}

void showCard::on_pushButton_clicked()
{
    emit clicked();
}

void showCard::setText(QString text)
{
    ui->pushButton->setText(text);
}
