#include "settings.h"
#include "ui_settings.h"
#include "global.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    if(ereader) {
        this->move(0, 0);
        this->setMinimumSize(ereaderVars::screen_x, ereaderVars::screen_y);
        this->setMaximumSize(ereaderVars::screen_x, ereaderVars::screen_y);
        this->adjustSize();
    }

    // This is because the QDialog has borders
    if(ereader) this->setStyleSheet("QDialog {border: 0px solid black; border-radius: 0px; background: white;}");

    // Set the default page
    ui->stackedWidget->setCurrentIndex(1);
    requestMenuPage();

    if(ereader) {
        ui->labelPageName->setStyleSheet("font-size: 9pt;");
        ui->ButtonLeft->setStyleSheet("font-size: 9pt; border: 0px solid black;");
        ui->ButtonRight->setStyleSheet("font-size: 9pt; border: 0px solid black;");
        ui->ButtonOk->setStyleSheet("font-size: 8pt; border: 0px solid black;");
    }

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_ButtonLeft_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    index = index - 1;
    managePage(index, Left);
}


void Settings::on_ButtonRight_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    index = index + 1;
    managePage(index, Right);
}


void Settings::requestEreaderPage()
{
    ui->labelPageName->setText("Device");

    check_battery_level();
    QString bat_level = "Battery level: ";
    bat_level.append(QString::number(ereaderVars::batt_level_int));
    bat_level.append("%");
    ui->labelBattery->setText(bat_level);

    int brightness = get_brightness();
    ui->ScrollBarBrightness->setSliderPosition(brightness);

    QString brightness_string = "Brightness: ";
    brightness_string.append(QString::number(brightness));
    brightness_string.append("%");
    ui->labelBrightness->setText(brightness_string);
}

void Settings::on_ScrollBarBrightness_valueChanged(int value)
{
    set_brightness(value);

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

void Settings::managePage(int newIndex, Direction fromWhere) {
    if(newIndex < 0) {
        newIndex = maxPageNumber;
    }
    if(newIndex > maxPageNumber) {
        newIndex = 0;
    }

    if(ereader != true && newIndex == 0) {
        if(fromWhere == Right) {
            managePage(newIndex + 1, fromWhere);
            return void();
        } else {
            managePage(newIndex - 1, fromWhere);
            return void();
        }
    }

    ui->stackedWidget->setCurrentIndex(newIndex);
    if(newIndex == 0) {
        requestEreaderPage();
    } else if(newIndex == 1) {
        requestMenuPage();
    }
}

void Settings::requestMenuPage() {
    ui->labelPageName->setText("Menu");
}
