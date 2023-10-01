#include "pomodoro.h"
#include "ui_pomodoro.h"

#include "global.h"
#include "QTimer"
#include "QSettings"
#include <QDebug>

pomodoro::pomodoro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pomodoro)
{
    ui->setupUi(this);
    // this->setAttribute(Qt::WA_DeleteOnClose); // This dialog stays
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint); // this closes the window, awesome

    ui->breakDurationBox->setStyleSheet("font-size: 9pt;");
    ui->longBreakDurationBox->setStyleSheet("font-size: 9pt;");
    ui->pomodoroDurationBox->setStyleSheet("font-size: 9pt;");
    ui->xBeforeBreakBox->setStyleSheet("font-size: 9pt;");
    ui->lcdNumber->setVisible(false);
    this->setFixedWidth(ereaderVars::screenX - 150);
    ui->tabWidget->setCurrentIndex(1);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &pomodoro::mainFunction);
    timer->setInterval(5000);

    settingsGlobal = new QSettings(directories::globalSettings.fileName(), QSettings::IniFormat);
    {
        QString key = "pomodoroLearningTime";
        if(settingsGlobal->contains(key)) {
            pomodoroDur = settingsGlobal->value(key).toInt();
        }
    }
    {
        QString key = "pomodoroBreakNormalTime";
        if(settingsGlobal->contains(key)) {
            breakNormalDur = settingsGlobal->value(key).toInt();
        }
    }
    {
        QString key = "pomodoroBreakLongTime";
        if(settingsGlobal->contains(key)) {
            breakLongDur = settingsGlobal->value(key).toInt();
        }
    }
    {
        QString key = "pomodorosUntilLong";
        if(settingsGlobal->contains(key)) {
            countPomodorosUntilLong = settingsGlobal->value(key).toInt();
        }
    }

    ui->pomodoroDurationBox->setValue(pomodoroDur);
    ui->breakDurationBox->setValue(breakNormalDur);
    ui->longBreakDurationBox->setValue(breakLongDur);
    ui->xBeforeBreakBox->setValue(countPomodorosUntilLong);
    timeLeftMax = pomodoroDur;
}

pomodoro::~pomodoro()
{
    delete ui;
}

QString pomodoro::timeLeftFun() {
    if(timer->isActive() == false) {
        return "OFF";
    }
    qDebug() << "timeLeftMax:" << timeLeftMax;
    int timeGoals = (timeLeftMax * 60) - timeLeft;

    // For status bar
    if(timeLeft < 0) {
        timeGoals = timeGoals - 5;
    }

    qDebug() << "timeGoals:" << timeGoals;
    int timeGoalsM = timeGoals / 60;
    int timeGoalsS = timeGoals - (timeGoalsM * 60);

    QString mStr = QString::number(timeGoalsM);
    if(timeGoalsM < 10) {
        mStr = "0" + mStr;
    }
    QString sStr = QString::number(timeGoalsS);
    if(timeGoalsS < 10) {
        sStr = "0" + sStr;
    }

    QString display = mStr + ":" + sStr;
    qDebug() << "display:" << display;
    return display;

    // Reverse of what here is
    /*
    int m = timeLeft / 60;
    int s = timeLeft - (m * 60);
    QString mStr = QString::number(m);
    if(m < 10) {
        mStr = "0" + mStr;
    }
    QString sStr = QString::number(s);
    if(s < 10) {
        sStr = "0" + sStr;
    }
    return mStr + ":" + sStr;
    */
}

// called every 5 sec
bool startPomodoro = false;
void pomodoro::mainFunction() {
    timeLeft = timeLeft + 5;
    int timeLeftM = timeLeft / 60;
    qDebug() << "timeLeftM:" << timeLeftM;
    if(status == pomodoroLearning) {
        if(timeLeftM >= pomodoroDur) {
            counterBreaks = counterBreaks + 1;
            if(counterBreaks >= countPomodorosUntilLong) {
                timeLeft = 0;
                counterBreaks = 0;
                status = breakLong;
                ui->statusLabel->setText("Long break");
                timeLeftMax = breakLongDur;
                ui->tabWidget->setCurrentIndex(1);
                this->show();
            } else {
                timeLeft = 0;
                settingsGlobal->sync();
                status = breakNormal;
                ui->statusLabel->setText("Normal break");
                timeLeftMax = breakNormalDur;
                ui->tabWidget->setCurrentIndex(1);
                this->show();
            }
            updateBreakLabel();
        } else {
            if(startPomodoro == false) {
                startPomodoro = true;
                timeLeftMax = pomodoroDur;
                ui->statusLabel->setText("Learning");
            }
        }
    } else if(status == breakNormal) {
        if(timeLeftM >= breakNormalDur) {
            timeLeft = 0;
            status = pomodoroLearning;
            timeLeftMax = pomodoroDur;
            ui->statusLabel->setText("Learning");
            ui->tabWidget->setCurrentIndex(1);
            this->show();
        }
    } else if(status == breakLong) {
        if(timeLeftM >= breakLongDur) {
            timeLeft = 0;
            status = pomodoroLearning;
            timeLeftMax = pomodoroDur;
            ui->statusLabel->setText("Learning");
            ui->tabWidget->setCurrentIndex(1);
            this->show();
        }
    }

    // Manage the LCD timer
    // Reverse of timeLeftFun to timeLeftMax
    if(this->isVisible()) {
        ui->lcdNumber->display(timeLeftFun());
    }
}

void pomodoro::updateBreakLabel() {
    ui->breakLabel->setText("Until long: " + QString::number(countPomodorosUntilLong - counterBreaks));
}

void pomodoro::on_enableBox_stateChanged(int arg1)
{
    //qDebug() << "arg1:" << arg1;
    if(arg1 == 2) {
        timer->start();
        ui->lcdNumber->setVisible(true);
        ui->verticalSpacer_2->changeSize(0, 0);
        mainFunction();
    } else {
        timer->stop();
        timeLeft = -5;
        counterBreaks = 0;
        ui->statusLabel->setText("OFF");
        startPomodoro = false;
        status = pomodoroLearning;
        ui->lcdNumber->setVisible(false);
        ui->verticalSpacer_2->changeSize(100, 100);
    }
    updateBreakLabel();
}

void pomodoro::on_pomodoroDurationBox_valueChanged(int arg1)
{
    pomodoroDur = arg1;
    settingsGlobal->setValue("pomodoroLearningTime", pomodoroDur);
}

void pomodoro::on_breakDurationBox_valueChanged(int arg1)
{
    breakNormalDur = arg1;
    settingsGlobal->setValue("pomodoroBreakNormalTime", breakNormalDur);
}

void pomodoro::on_longBreakDurationBox_valueChanged(int arg1)
{
    breakLongDur = arg1;
    settingsGlobal->setValue("pomodoroBreakLongTime", breakLongDur);
}

void pomodoro::on_xBeforeBreakBox_valueChanged(int arg1)
{
    countPomodorosUntilLong = arg1;
    settingsGlobal->setValue("pomodorosUntilLong", countPomodorosUntilLong);
}
