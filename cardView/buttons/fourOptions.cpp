#include "fourOptions.h"
#include "global.h"
#include "ui_fourOptions.h"

#include <QTimer>

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
        this->setFixedHeight(125);
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

#define BUTTON_DELAY 650

void fourOptions::showButtons() {
    QTimer::singleShot(BUTTON_DELAY, this, [this]() {
        QApplication::processEvents();
        ui->stackedWidget->setCurrentIndex(0);
    });
}

void fourOptions::hideButtons() {
    QTimer::singleShot(BUTTON_DELAY, this, [this]() {
        QApplication::processEvents();
        ui->stackedWidget->setCurrentIndex(1);
    });
}
