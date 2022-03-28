#include "mainwindow.h"
#include "widgget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    for (int i = 0; i < 10; i++) {
        QWidget* idk = new widgget();
        w.add_widget(idk);
    }
    return a.exec();
}
