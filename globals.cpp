#include <globals.h>

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QTextCodec>

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
// https://stackoverflow.com/questions/61735609/implicit-instantiation-of-undefined-template-std-1basic-istringstreamchar
#include <sstream>
// https://stackoverflow.com/questions/1057287/ofstream-error-in-c
#include <fstream>

bool debug_enabled = false;
QDir directories::work_dir = QDir::homePath();
QDir directories::deck_storage = QDir::homePath() + "/decks";
QString kobo_model = "";
bool running_on_kobo = false;
int screen_x = 1920;
int screen_y = 1080;
int batt_level_int = 100;

void debugLog(QString Message, QString file, QString function)
{
    if (debug_enabled == true)
    {
        qDebug() << "LOG:" << Message << "| file" << file << "| function:" << function;
    }
}

void check_device()
{
    // If its running on kobo
    if(qgetenv("QT_QPA_PLATFORM") == "kobo")
    {
        kobo_model = qgetenv("DEVICE_CODENAME");
        kobo_model = kobo_model.remove("\n"); // Yes, just to be sure
        running_on_kobo = true;

        QString message = "Sanki is running on a kobo " + kobo_model;
        debugLog(message, "globals.h", "check_device()");
    } else {
        running_on_kobo = false;
        debugLog("Sanki is not running on a kobo", "globals.h", "check_device()");
    }
}


// This function creates all global variables that need to be accesed at the begging
void screen_geometry()
{
    // Window geometry
    QRect screenGeometry = QGuiApplication::screens()[0]->geometry();
    screen_x = screenGeometry.width();
    screen_y = screenGeometry.height();
    QString message;
    message.append("Screen size is x:");
    message.append(QString::number(screen_x));
    message.append(" y:");
    message.append(QString::number(screen_y));
    debugLog(message, "globals.h", "screen_geometry()");
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

        batt_level_int = batt_level.toInt();
        batt_level_file.close();
    }
    else {
        batt_level_int = 100;
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
