#include "settings.h"
#include "ui_settings.h"
#include "globals.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->move(0, 0);
    this->setMinimumSize(global_var::screen_x, global_var::screen_y);
    this->setMaximumSize(global_var::screen_x, global_var::screen_y);
    this->adjustSize();

    // This is becouse the QDialog has borders
    this->setStyleSheet("QDialog {border: 0px solid black; border-radius: 0px; background: white;}");

    // Set the default page
    ui->stackedWidget->setCurrentWidget(ui->Page1Device);
    request_device_page();

    ui->labelPageName->setStyleSheet("font-size: 9pt;");
    ui->ButtonLeft->setStyleSheet("font-size: 9pt; border: 0px solid black;");
    ui->ButtonRight->setStyleSheet("font-size: 9pt; border: 0px solid black;");
    ui->ButtonOk->setStyleSheet("font-size: 8pt; border: 0px solid black;");
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_ButtonLeft_clicked()
{

}


void Settings::on_ButtonRight_clicked()
{

}


void Settings::request_device_page()
{
    ui->labelPageName->setText("Device");
    QString bat_level = "Battery level: ";
    bat_level.append(QString::number(global_var::batt_level_int));
    bat_level.append("%");
    ui->labelBattery->setText(bat_level);

    int brightness = global_fun::get_brightness();
    ui->ScrollBarBrightness->setSliderPosition(brightness);

    QString brightness_string = "Brightness: ";
    brightness_string.append(QString::number(brightness));
    brightness_string.append("%");
    ui->labelBrightness->setText(brightness_string);
}

void Settings::on_ScrollBarBrightness_valueChanged(int value)
{
    global_fun::set_brightness(value);

    QString brightness_string = "Brightness: ";
    QString number = QString::number(value);


    brightness_string.append(QString::number(value));
    brightness_string.append("%");

    ui->labelBrightness->setText(brightness_string);
}


void Settings::on_ButtonOk_clicked()
{
    this->close();
}

