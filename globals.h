#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
// https://stackoverflow.com/questions/61735609/implicit-instantiation-of-undefined-template-std-1basic-istringstreamchar
#include <sstream>
// https://stackoverflow.com/questions/1057287/ofstream-error-in-c
#include <fstream>

namespace global_var {
    inline bool debug_enabled = true;
    namespace directories {
        // Get current dir + deck storage paths
        inline QDir work_dir = QDir::current();
        //qDebug() << "work_dir" << work_dir.path();

        inline QDir deck_storage = work_dir.path() + "/deck_storage";
        //qDebug() << "deck_storage" << deck_storage.path();
    }
    inline QString kobo_model;
    inline bool running_on_kobo;
    inline int screen_x;
    inline int screen_y;
    inline int batt_level_int;


}

namespace global_fun {
    inline void log(QString Message, QString file, QString function)
    {
        if (global_var::debug_enabled == true)
        {
            qDebug() << "LOG:" << Message << "| file" << file << "In function:" << function;
        }
    }

    inline void check_device()
    {
        // If its running on kobo
        QFile device_file("/opt/inkbox_device");
        if(device_file.exists() == true)
        {
            device_file.open(QIODevice::ReadOnly);
            global_var::kobo_model = device_file.readAll();
            global_var::kobo_model = global_var::kobo_model.remove("\n"); // Yes
            device_file.close();
            global_var::running_on_kobo = true;

            QString message = "Sanki is running on a kobo " + global_var::kobo_model;
            global_fun::log(message, "globals.h", "check_device()");
        } else {
            global_var::running_on_kobo = false;
            global_fun::log("Sanki is not running on a kobo", "globals.h", "check_device()");
        }
    }


    // This function creates all global variables that need to be accesed at the begging
    inline void screen_geometry()
    {
        // Window geometry
        QRect screenGeometry = QGuiApplication::screens()[0]->geometry();
        global_var::screen_x = screenGeometry.width();
        global_var::screen_y = screenGeometry.height();
        QString message;
        message.append("Screen size is x:");
        message.append(QString::number(global_var::screen_x));
        message.append(" y:");
        message.append(QString::number(global_var::screen_y));
        global_fun::log(message, "globals.h", "screen_geometry()");
    }
    inline void check_battery_level()
    {
        // Copied from inkbox
        QFile batt_level_file("/sys/devices/platform/pmic_battery.1/power_supply/mc13892_bat/capacity");
        QString batt_level;
        if(batt_level_file.exists()) {
            batt_level_file.open(QIODevice::ReadOnly);
            batt_level = batt_level_file.readAll();
            batt_level = batt_level.trimmed();
            global_var::batt_level_int = batt_level.toInt();
            batt_level_file.close();
        }
        else {
            global_var::batt_level_int = 100;
        }
    }
    inline void set_brightness(int value) {
        std::ofstream fhandler;
        fhandler.open("/var/run/brightness");
        fhandler << value;
        fhandler.close();
    }
    inline int get_brightness() {
        QFile brightness("/var/run/brightness");
        brightness.open(QIODevice::ReadOnly);
        QString valuestr = brightness.readAll();
        int value = valuestr.toInt();
        brightness.close();
        return value;
    }
}
#endif // GLOBALS_H
