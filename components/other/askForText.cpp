#include "askForText.h"
#include "ui_askForText.h"

askForText::askForText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askForText)
{
    ui->setupUi(this);
}

askForText::~askForText()
{
    delete ui;
}
