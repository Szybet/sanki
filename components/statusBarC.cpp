#include "components/statusBarC.h"
#include "ui_statusBarC.h"
#include "settings.h"
#include "global.h"

#include <QTimer>
#include <QTime>
#include <QDebug>

statusBarC::statusBarC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusBarC)
{
    ui->setupUi(this);

    // Set up timer for time showing
    if(ereader) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &statusBarC::showTime);
        timer->start(1000);
        showTime();
    }

    if(pc) {
        ui->ButtonExit->hide();
        ui->lineExit->hide();
        ui->LineTime->hide();
        ui->labelTime->hide();

        ui->horizontalSpacerTime_5->changeSize(0,0);
        ui->horizontalSpacerTime_6->changeSize(0,0);
        ui->horizontalSpacerExit_3->changeSize(0,0);
        ui->horizontalSpacerExit_4->changeSize(0,0);
    }

    ui->ButtonExit->setStyleSheet("border: none;");
    ui->ButtonSettings->setStyleSheet("border: none;");
}

statusBarC::~statusBarC()
{
    delete ui;
}

void statusBarC::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    ui->labelTime->setText(text);
}

void statusBarC::OptionButtonSet(QString text, QIcon icon, bool enabled)
{
    ui->ButtonOption->setVisible(enabled);
    if(enabled == true) {
        ui->ButtonOption->setStyleSheet("font-size: 9pt");
        ui->ButtonOption->setIcon(icon);
        ui->ButtonOption->setText(text);
    }
}

void statusBarC::OptionButtonSet2(QString text, QIcon icon, bool enabled)
{
    ui->ButtonOption_2->setVisible(enabled);
    ui->lineOption_2->setVisible(enabled);
    if(enabled == true) {
        ui->ButtonOption_2->setStyleSheet("font-size: 9pt");
        ui->ButtonOption_2->setIcon(icon);
        ui->ButtonOption_2->setText(text);
    }
}

void statusBarC::on_ButtonExit_clicked()
{
    emit closeButtonSignal();
}


void statusBarC::on_ButtonOption_clicked()
{
    emit optionButtonSignal();
}


void statusBarC::on_ButtonSettings_clicked()
{
    Settings* settings_qdialog = new Settings;
    settings_qdialog->exec();
}

void statusBarC::on_ButtonOption_2_clicked()
{
    emit option2ButtonSignal();
}

