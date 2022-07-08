#include "main_menu/mainwindow.h"
#include "globals.h"

#include <QApplication>
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    if(qgetenv("DEBUG") == "true")
    {
        global_var::debug_enabled = true;
        qDebug() << "Debug logs are enabled";
    } else {
        global_var::debug_enabled = false;
        qDebug() << "Debug logs are disabled, goodbye";
    }
    global_fun::log("Sanki started", "main.cpp", "main()");

    QApplication a(argc, argv);
    // Very fuc... important. Do it after creating QAPPLICATION:
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    // Check and apply stylesheet if available
    global_fun::screen_geometry();
    global_fun::check_device();
    if(global_var::running_on_kobo == true)
    {
        // inkbox user app
        //QFile style_file("/mnt/onboard/.adds/inkbox/eink.qss");
        QFile style_file("/etc/eink.qss");

        if(style_file.exists() == false)
        {
            global_fun::log("stylesheet file doesn't exist", "main.cpp", "main()");
        }

        style_file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(style_file.readAll());
        a.setStyleSheet(styleSheet);
    }

    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
