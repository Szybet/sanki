#include "session.h"
#include "ui_session.h"
#include "mainMenu/sessions/editSession.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QMouseEvent>
#include <QSettings>
#include <QTimer>

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

    showRegularStats();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &session::statsManager);
    timer->start(800);
}

void session::on_ButtonDeckPlay_clicked()
{
    emit playSession(sessionSaved);
}

void session::on_ButtonOptions_clicked()
{
    editSession* editSessionDialog = new editSession(this);
    connect(editSessionDialog, &editSession::refreshSessionsSignal, this, &session::refreshSessionsSlot);
    editSessionDialog->start(sessionSaved);
    editSessionDialog->exec();
}

void session::refreshSessionsSlot() {
    emit refreshSessionsSignal();
}

void session::showRegularStats() {
    ui->LabelStats->setText(getSmallStatsForSession(&sessionSaved, true));
}

void session::showFocusedStats() {
    ui->LabelStats->setText(getStatsForSession(&sessionSaved, true, false));
}

void session::statsManager() {
    if(ui->LabelStats->underMouse() == true || ui->LabelStats->hasFocus() == true) {
        showFocusedStats();
        normalStats = false;
    } else {
        if(normalStats == false) {
            showRegularStats();
            normalStats = true;
        }
    }
}
