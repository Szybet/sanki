#include <global.h>

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QTextCodec>
#include <QStandardPaths>

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
// https://stackoverflow.com/questions/61735609/implicit-instantiation-of-undefined-template-std-1basic-istringstreamchar
#include <sstream>
// https://stackoverflow.com/questions/1057287/ofstream-error-in-c
#include <fstream>

// Default values
bool debugEnabled = false;

bool pc = false;
bool ereader = false;

QDir directories::config = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "sanki";
QDir directories::deckStorage = directories::config.path() + QDir::separator() + "decks";
QDir directories::sessionSaves = directories::config.path() + QDir::separator() + "sessions";
QDir directories::deckSelect = QDir::homePath();

QString ereaderVars::model = "";
int ereaderVars::screen_x = 1920;
int ereaderVars::screen_y = 1080;
int ereaderVars::batt_level_int = 100;

void check_device()
{
    // If its running on kobo
    if(qgetenv("QT_QPA_PLATFORM") == "kobo")
    {
        ereaderVars::model = qgetenv("DEVICE_CODENAME");
        ereaderVars::model = ereaderVars::model.remove("\n"); // Yes, just to be sure

        qDebug() << "Sanki is running on a kobo " << ereaderVars::model;
    } else {
        qDebug() << "Sanki is not running on a kobo";
    }
}


// This function creates all global variables that need to be accesed at the begging
void screen_geometry()
{
    // Window geometry
    QRect screenGeometry = QGuiApplication::screens()[0]->geometry();
    ereaderVars::screen_x = screenGeometry.width();
    ereaderVars::screen_y = screenGeometry.height();
    qDebug() << "Screen size is x:" << ereaderVars::screen_x << "y:" << ereaderVars::screen_y;
}
void check_battery_level()
{
    // Copied from inkbox
    QFile batt_level_file("/sys/devices/platform/pmic_battery.1/power_supply/mc13892_bat/capacity");
    QString batt_level;
    if(batt_level_file.exists()) {
        batt_level_file.open(QIODevice::ReadOnly);
        batt_level = batt_level_file.readAll();
        batt_level = batt_level.trimmed();

        //QString message = "Battery level is: ";
        //message.append(batt_level);
        //debugLog(message, "globals.h", "check_battery_level");

        ereaderVars::batt_level_int = batt_level.toInt();
        batt_level_file.close();
    }
    else {
        ereaderVars::batt_level_int = 100;
    }
}
void set_brightness(int value) {
    // doesnt work
    std::ofstream fhandler;
    fhandler.open("/var/run/brightness");
    fhandler << value;
    fhandler.close();
}

int get_brightness() {
    // doesnt work
    QFile brightness("/var/run/brightness");
    brightness.open(QIODevice::ReadOnly);
    QString valuestr = brightness.readAll();
    int value = valuestr.toInt();
    brightness.close();
    return value;
    return 0;
}
