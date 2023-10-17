#include "fourOptionsNFlashy.h"
#include "global.h"
#include "ui_fourOptionsNFlashy.h"

#include <QTimer>
#include <QDebug>

fourOptionsNFlashy::fourOptionsNFlashy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourOptionsNFlashy)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    if(ereader) {
        ui->againButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->hardButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->goodButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        ui->easyButton->setStyleSheet(ereaderVars::buttonNoFlashStylesheet);
        this->setFixedHeight(125);
    }
}

fourOptionsNFlashy::~fourOptionsNFlashy()
{
    delete ui;
}

void fourOptionsNFlashy::on_againButton_clicked()
{
    if(enabledButtons == true) {
        emit again();
        enabledButtons = false;
    }
}

void fourOptionsNFlashy::on_hardButton_clicked()
{
    if(enabledButtons == true) {
        emit hard();
        enabledButtons = false;
    }
}

void fourOptionsNFlashy::on_goodButton_clicked()
{
    if(enabledButtons == true) {
        emit good();
        enabledButtons = false;
    }
}

void fourOptionsNFlashy::on_easyButton_clicked()
{
    if(enabledButtons == true) {
        emit easy();
        enabledButtons = false;
    }
}

void fourOptionsNFlashy::enableButtons() {
    qDebug() << "Enabled buttons for fourOptionsNFlashy";
    // Delay for skipping any button that would accour of taps inside this widget
    QTimer::singleShot(100, this, [this]() {
        enabledButtons = true;
    });
}
