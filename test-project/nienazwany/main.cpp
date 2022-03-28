#include "mainwindow.h"
#include "widgget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QWidget* idk = new widgget();
    w.add_widget(idk);
    return a.exec();
}
