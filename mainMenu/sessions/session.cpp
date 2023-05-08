#include "session.h"
#include "ui_session.h"

#include <QSettings>

session::session(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::session)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

session::~session()
{
    delete ui;
}

void session::start(QString path) {
    qDebug() << "Called start to session with path:" << directories::sessionSaves.filePath(path);
    QSettings settings(directories::sessionSaves.filePath(path), QSettings::IniFormat);
    settings.sync();

    qDebug() << "Settings session valid:" << settings.value("session").isValid();

    sessionSaved = settings.value("session").value<sessionStr>();

    qDebug() << "Settings status:" << settings.status();

    qDebug() << "Readed session from path:" << path << "it is:" << sessionSaved;

    ui->sessionName->setText(sessionSaved.core.name);
}

void session::on_ButtonDeckPlay_clicked()
{
    emit playSession(sessionSaved);
}


void session::on_ButtonOptions_clicked()
{

}

