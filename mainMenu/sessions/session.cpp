#include "session.h"
#include "ui_session.h"

#include <QSettings>

session::session(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::session)
{
    ui->setupUi(this);
}

session::~session()
{
    delete ui;
}

void session::start(QString path) {
    QSettings settings(path, QSettings::IniFormat);
    sessionSaved = settings.value("session").value<sessionStr>();

    qDebug() << "Readed session from path:" << path << "it is:" << sessionSaved;
}
