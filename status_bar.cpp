#include "status_bar.h"
#include "ui_status_bar.h"

#include <QTimer>
#include <QTime>
#include <QDebug>

status_bar::status_bar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::status_bar)
{
    ui->setupUi(this);

    // Set up timer for time showing
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &status_bar::showTime);
    timer->start(1000);
    showTime();

    ui->ButtonExit->setStyleSheet("border: none;");
    ui->ButtonSettings->setStyleSheet("border: none;");

}

status_bar::~status_bar()
{
    delete ui;
}

void status_bar::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    ui->labelTime->setText(text);
}

void status_bar::option_button_set(QString button_text, QIcon icon)
{
    ui->ButtonOption->setStyleSheet("font-size: 10pt");
    ui->ButtonOption->setIcon(icon);
    ui->ButtonOption->setText(button_text);
}

void status_bar::on_ButtonExit_clicked()
{
    emit close_button_signal();
}


void status_bar::on_ButtonOption_clicked()
{
    emit option_button_signal();
}

