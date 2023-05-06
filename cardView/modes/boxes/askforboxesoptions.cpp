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
}

askForBoxesOptions::~askForBoxesOptions()
{
    delete ui;
}

void askForBoxesOptions::start(boxes* parentArg) {
    parent = parentArg;
    ui->againSpinBox->setValue(parent->theBox.againValue);
    ui->hardSpinBox_2->setValue(parent->theBox.hardValue);
    ui->goodSpinBox_3->setValue(parent->theBox.goodValue);
    ui->easySpinBox_4->setValue(parent->theBox.easyValue);
    ui->boxesSpinBox->setValue(parent->theBox.howMuchBoxes);
    ui->skipSpinBox->setValue(parent->theBox.defaultSkipValue);
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
    parent->theBox.againValue = arg1;
}

void askForBoxesOptions::on_hardSpinBox_2_valueChanged(int arg1)
{
    parent->theBox.hardValue = arg1;
}

void askForBoxesOptions::on_goodSpinBox_3_valueChanged(int arg1)
{
    parent->theBox.goodValue = arg1;
}

void askForBoxesOptions::on_easySpinBox_4_valueChanged(int arg1)
{
    parent->theBox.easyValue = arg1;
}

void askForBoxesOptions::on_boxesSpinBox_valueChanged(int arg1)
{
    parent->theBox.howMuchBoxes = arg1;
}

void askForBoxesOptions::on_skipSpinBox_valueChanged(int arg1)
{
    parent->theBox.defaultSkipValue = arg1;
}

