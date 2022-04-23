#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>

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
        QFile device_file("/opt/device");
        if(device_file.exists() == true)
        {
            global_var::kobo_model = device_file.readAll();
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
}
#endif // GLOBALS_H
