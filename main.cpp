#include "mainwindow.h"
#include "globals.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    global_fun::log("Sanki started test 12", "main.cpp", "main()");

    QApplication a(argc, argv);

    // Check and apply stylesheet if available
    global_fun::screen_geometry();
    global_fun::check_device();
    if(global_var::running_on_kobo == true)
    {
        QFile style_file("/mnt/onboard/.adds/inkbox/eink.qss");
        style_file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(style_file.readAll());
        a.setStyleSheet(styleSheet);
    }

    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
