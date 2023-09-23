#include "askforboxesoptions.h"
#include "ui_askforboxesoptions.h"

#include <QMessageBox>

askForBoxesOptions::askForBoxesOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askForBoxesOptions)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->label->setAlignment(Qt::AlignCenter);

    ui->infoButton->setIcon(QIcon(":/icons/info.svg"));

    if(ereader) {
        QString spaces = "   ";
        ui->againSpinBox->setSuffix(spaces);
        ui->hardSpinBox_2->setSuffix(spaces);
        ui->goodSpinBox_3->setSuffix(spaces);
        ui->easySpinBox_4->setSuffix(spaces);
        ui->boxesSpinBox->setSuffix(spaces);
        ui->skipSpinBox->setSuffix(spaces);
        ui->startingBoxSpixBox->setSuffix(spaces);
    }
}

askForBoxesOptions::~askForBoxesOptions()
{
    delete ui;
}

void askForBoxesOptions::start(box* parentArg) {
    boxEdit = parentArg;
    ui->againSpinBox->setValue(boxEdit->againValue);
    ui->hardSpinBox_2->setValue(boxEdit->hardValue);
    ui->goodSpinBox_3->setValue(boxEdit->goodValue);
    ui->easySpinBox_4->setValue(boxEdit->easyValue);
    ui->boxesSpinBox->setValue(boxEdit->howMuchBoxes);
    ui->skipSpinBox->setValue(boxEdit->defaultSkipValue);
    ui->startingBoxSpixBox->setValue(boxEdit->startingBox);
}

void askForBoxesOptions::on_acceptButton_clicked()
{
    this->close();
}

void askForBoxesOptions::on_infoButton_clicked()
{
    qInfo() << "Those \"Buttons\" options indicate how much which button will move a card arround boxes\nSkip value is used to avoid showing the card until x other cards are shown";
}

void askForBoxesOptions::on_againSpinBox_valueChanged(int arg1)
{
    boxEdit->againValue = arg1;
}

void askForBoxesOptions::on_hardSpinBox_2_valueChanged(int arg1)
{
    boxEdit->hardValue = arg1;
}

void askForBoxesOptions::on_goodSpinBox_3_valueChanged(int arg1)
{
    boxEdit->goodValue = arg1;
}

void askForBoxesOptions::on_easySpinBox_4_valueChanged(int arg1)
{
    boxEdit->easyValue = arg1;
}

void askForBoxesOptions::on_boxesSpinBox_valueChanged(int arg1)
{
    boxEdit->howMuchBoxes = arg1;
}

void askForBoxesOptions::on_skipSpinBox_valueChanged(int arg1)
{
    boxEdit->defaultSkipValue = arg1;
}

void askForBoxesOptions::on_startingBoxSpixBox_valueChanged(int arg1)
{
    if(arg1 <= ui->boxesSpinBox->value()) {
        boxEdit->startingBox = arg1;
    } else {
        ui->startingBoxSpixBox->setValue(arg1 - 1);
    }
}
