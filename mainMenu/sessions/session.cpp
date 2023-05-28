#include "session.h"
#include "ui_session.h"
#include "mainMenu/sessions/editSession.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QMouseEvent>
#include <QSettings>
#include <QTimer>
#include <QToolTip>

session::session(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::session)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    if(ereader) {
        qDebug() << "Applying ereader settings in session";
        //ui->sessionName->setStyleSheet("font-size: 9pt");
        //ui->ButtonOptions->setStyleSheet("font-size: 6pt");
        //ui->ButtonDeckPlay->setStyleSheet("font-size: 6pt");
        ui->LabelStats->setStyleSheet("font-size: 7pt");
        //ui->frame->setContentsMargins(0, 0, 0, 0);
    }
}

session::~session()
{
    delete ui;
}

void session::start(QString path) {
    qDebug() << "Called start to session with path:" << directories::sessionSaves.filePath(path);
    QSettings settings(directories::sessionSaves.filePath(path), QSettings::IniFormat);
    settings.setParent(this);
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

    QFont font("Arial", 7);
    QToolTip::setFont(font);
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
    ui->LabelStats->setText(getSmallStatsForSession(sessionSaved, true));
}

void session::showFocusedStats() {
    QString info = getStatsForSession(sessionSaved, true, false, false);
    qDebug() << "Focused info length:" << info.length();
    // It crashes sometimes if it's too big? ereader specific
    if(info.length() > 220 && info.length() < 500) {
        if(QToolTip::isVisible() == false) {
            QApplication::processEvents();
            QToolTip::showText( ui->LabelStats->mapToGlobal( QPoint( 0, 0 ) ), info);
            QApplication::processEvents();
        } else {
            QToolTip::hideText();
        }
    } else {
        ui->LabelStats->setText(info);
    }
}

void session::statsManager() {
    if(ui->LabelStats->hasFocus() == true) {
        if(changedFocus == true) {
            showFocusedStats();
            normalStats = false;
            changedFocus = false;
        }
    } else {
        changedFocus = true;
        if(normalStats == false) {
            showRegularStats();
            normalStats = true;
        }
    }
}

void session::on_sessionName_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
    ui->sessionName->setSelection(0, 0);
    if(startBoolIgnoreChanged == false) {
        ui->sessionName->setSelection(0, 0);
        if(QToolTip::isVisible() == false) {
            QApplication::processEvents();
            QToolTip::showText( ui->sessionName->mapToGlobal( QPoint( 0, 0 ) ), ui->sessionName->text());
            QApplication::processEvents();
        } else {
            QToolTip::hideText();
        }
    } else {
        startBoolIgnoreChanged = false;
    }
}

