#include "settingsMenu.h"
#include "ui_settingsMenu.h"

#include "global.h"

#include <QDebug>
#include <QTimer>
#include <QMouseEvent>

settingsMenu::settingsMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingsMenu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->pomodoroButton->setStyleSheet("Text-align: left");
    ui->settingsButton->setStyleSheet("Text-align: left");
    ui->refreshButton->setStyleSheet("Text-align: left");
}

settingsMenu::~settingsMenu()
{
    delete ui;
}

void settingsMenu::start(pomodoro* pomodoroWidgetParent, statusBarC* statusBarParent) {
    pomodoroWidget = pomodoroWidgetParent;
    statusBar = statusBarParent;

    // Point size is not available?
    QApplication::processEvents();
    QFont font = ui->batteryLabel->font();
    font.setPixelSize(20);
    ui->batteryLabel->setFont(font);
    ui->brightnessLabel->setFont(font);
    ui->pomodoroLabel->setFont(font);

    int battLev = checkBatteryLevel();
    ui->batteryLabel->setText(QString::number(battLev) + "%");
    qDebug() << "battLev:" << battLev;

    QSize iconSize(24, 24);

    if(battLev > 80) {
        ui->batteryIcon->setPixmap(QIcon(":/icons/battery_full.png").pixmap(iconSize));
    } else if(battLev > 40) {
        ui->batteryIcon->setPixmap(QIcon(":/icons/battery_half.png").pixmap(iconSize));
    } else {
        ui->batteryIcon->setPixmap(QIcon(":/icons/battery_empty.png").pixmap(iconSize));
    }

    ui->brightnessIcon->setPixmap(QIcon(":/icons/brightness.png").pixmap(iconSize));
    ui->brightnessLabel->setText(QString::number(getWhiteBrightnessAlias()) + "%");

    if(pomodoroWidget->timeLeftFun() == "OFF") {
        ui->pomodoroLabel->setText(pomodoroWidget->timeLeftFun());
    } else {
        ui->pomodoroLabel->setText("Left: " +  pomodoroWidget->timeLeftFun());
    }

    // There is a small line below...
    /*)
    QTimer::singleShot(5000, this, [this]() {
        QRect refreshRectLine;
        refreshRectLine.setX(this->pos().x());
        refreshRectLine.setY(this->pos().y());
        refreshRectLine.setSize(this->size());
        qDebug() << "refreshRectLine:" << refreshRectLine;
        refreshRectLine.setY(refreshRectLine.y() + refreshRectLine.height());
        refreshRectLine.setHeight(700);
        refreshRect(refreshRectLine, true, WFM_GC4);
    });
    */
    // This doesn't work
}

void settingsMenu::on_settingsButton_clicked()
{
    statusBar->openSettings();
    this->close();
}

void settingsMenu::on_pomodoroButton_clicked()
{
    statusBar->pomodoroWidget->setModal(true);
    statusBar->pomodoroWidget->show();
    this->close();
}

void settingsMenu::on_refreshButton_clicked()
{
    // Because of closing the dialog fully and the bottom line stays
    QTimer::singleShot(1200, statusBar, []() {
        refreshRect(QRect(0, 0, ereaderVars::screenX, ereaderVars::screenY));
        loadWaveFormSetting();
    });
    this->close();
}
