#include "mainwindow.h"
#include "globals.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Sanki started kurwa co jest";
    // This checks if the device is running on a e-reader, and on which device model
    QFile device_file("/opt/device");
    if(device_file.exists() == true)
    {
        kobo_model = device_file.readAll();
        running_on_kobo = true;
        qDebug() << "Sanki is running on inkbox, on the " << kobo_model << "model";
    } else {
        running_on_kobo = false;
        qDebug() << "Sanki is not running on inkbox";
    }

    QApplication a(argc, argv);

    if(running_on_kobo == true)
    {
        QFile style_file("/mnt/onboard/.adds/inkbox/eink.qss");
        style_file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(style_file.readAll());
        a.setStyleSheet(styleSheet);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
