#include "fourOptions.h"
#include "global.h"
#include "ui_fourOptions.h"

fourOptions::fourOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourOptions)
{
    ui->setupUi(this);
    if(ereader) {
        ui->againButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->hardButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->goodButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->easyButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->showButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
    }
    hideButtons();
}

fourOptions::~fourOptions()
{
    delete ui;
}

void fourOptions::on_againButton_clicked()
{
    hideButtons();
    emit again();
}

void fourOptions::on_hardButton_clicked()
{
    hideButtons();
    emit hard();
}

void fourOptions::on_goodButton_clicked()
{
    hideButtons();
    emit good();
}

void fourOptions::on_easyButton_clicked()
{
    hideButtons();
    emit easy();
}

void fourOptions::on_showButton_clicked()
{
    showButtons();
    emit show();
}

void fourOptions::showButtons() {
    ui->stackedWidget->setCurrentIndex(0);
}

void fourOptions::hideButtons() {
    ui->stackedWidget->setCurrentIndex(1);
}
