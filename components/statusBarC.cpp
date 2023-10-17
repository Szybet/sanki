#include "components/statusBarC.h"
#include "ui_statusBarC.h"
#include "settings.h"
#include "global.h"
#include "settings/settingsMenu.h"

#include <QTimer>
#include <QTime>
#include <QDebug>

#ifdef EREADER
#include "devicedescriptor.h"
#include "devbattery.h"
#include "devbrightness.h"
#include "einkenums.h"
#include "koboplatformfunctions.h"
#endif

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
        ui->horizontalSpacerTime_5->changeSize(0,0);
        ui->horizontalSpacerTime_6->changeSize(0,0);

        ui->labelTime->setVisible(false);
        ui->LineTime->setVisible(false);
    }


    if(ereader) {
        ui->ButtonExit->setStyleSheet("border: none;");
        ui->ButtonSettings->setStyleSheet("border: none;");
        ui->ButtonStatus->setStyleSheet(ereaderVars::buttonNoFlashStylesheet + " QPushButton { border: none; }");
    }
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

bool pomodoroCreated = false;
void statusBarC::on_ButtonSettings_clicked()
{
    if(grender) {
        KoboPlatformFunctions::setFullScreenRefreshMode(WaveForm::WaveForm_A2);
    }

    if(pomodoroCreated == false) {
        pomodoroWidget = new pomodoro(); // parent issue with showing?
        pomodoroCreated = true;
    }

    settingsMenu* menu = new settingsMenu();
    menu->setWindowModality(Qt::ApplicationModal);
    QPoint menuLoc = ui->ButtonSettings->pos();
    menuLoc.setY(menuLoc.y() + ui->ButtonSettings->size().height());
    qDebug() << "settingsMenu size is:" << menu->size();

    int menuMaxX = (menuLoc.x() + menu->size().width());
    qDebug() << "menuMaxX:" << menuMaxX;
    int x = menuMaxX - ereaderVars::screenX;
    if(x < 0) {
        x = x * -1;
    }
    qDebug() << "X above is:" << x;
    x = x + 15;
    menuLoc.setX(menuLoc.x() - x);

    menu->move(menuLoc);
    menu->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint); // this closes the window, awesome
    menu->start(pomodoroWidget, this);
    menu->show();

    QApplication::processEvents();

    if(grender) {
        loadWaveFormSetting();
    }
}

void statusBarC::openSettings() {
    Settings* settings_qdialog = new Settings;
    settings_qdialog->exec();
    emit refreshDecksSignal();
    emit closedOptionsDialog();
}

void statusBarC::on_ButtonOption_2_clicked()
{
    emit option2ButtonSignal();
}

void statusBarC::OptionButtonExit(QIcon icon, bool enabled) {
    if(enabled == false) {
        ui->ButtonExit->hide();
        ui->lineExit->hide();
        ui->LineTime->hide();
        ui->labelTime->hide();

        ui->horizontalSpacerExit_3->changeSize(0,0);
        ui->horizontalSpacerExit_4->changeSize(0,0);
    } else {
        ui->ButtonExit->setIcon(icon);
        ui->ButtonExit->show();
        ui->lineExit->show();
        ui->LineTime->show();
        ui->labelTime->show();

        ui->horizontalSpacerExit_3->changeSize(10,0);
        ui->horizontalSpacerExit_4->changeSize(10,0);
    }

}

void statusBarC::on_ButtonStatus_clicked()
{
    if(ui->ButtonStatus->text() == "Sanki") {
        qInfo() << "Sanki, a small anki app<br>"
                   "Created by Szybet<br>"
                   "https://github.com/Szybet/sanki<br>"
                   "If you appreciate this app, consider supporting it in any way";
    }
}

void statusBarC::setStatusText(QString text) {
    ui->ButtonStatus->setText(text);
}
