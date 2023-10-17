#include "cardView/modes/boxes/askforboxesoptions.h"
#include "components/other/keyboard.h"
#include "editSession.h"
#include "ui_editSession.h"
#include "components/other/statistics.h"

#include <QDebug>


editSession::editSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editSession)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setModal(true);

    if(ereader) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &editSession::manageKeyboards);
        timer->start(800);
    }
}

editSession::~editSession()
{
    delete ui;
}

void editSession::start(sessionStr session) {
    sessionSaved = session;
    if(sessionSaved.core.mode != Boxes) {
        ui->comboBox->removeItem(1);
    }
    ui->lineEdit->setText(sessionSaved.core.name);
    settingsSession = new QSettings(directories::sessionSaves.filePath(session.core.name), QSettings::IniFormat);
    settingsSession->sync();
}

void editSession::on_cancelButton_clicked() {
    qDebug() << "Cancel button clicked";
    this->close();
}

void editSession::on_comboBox_textActivated(const QString &arg1) {
    qDebug() << "Combobox button clicked" << arg1;
    if(arg1 == "Show full statistics") {
        statistics* newStats = new statistics(this);
        newStats->show(); // To make it calculate document size VERY IMPORTANT https://stackoverflow.com/questions/22457332/why-does-qtextedit-have-sometimes-document-height-0
        newStats->start(sessionSaved);
        newStats->exec();
    } else if(arg1 == "Box mode settings") {
        if(settingsSession->value("boxMode/box").isNull() == true && settingsSession->value("boxMode/box").isValid() == false)
        {
            qWarning() << "There is no saved data for this deck, for box mode";
        } else {
            boxesSettings = settingsSession->value("boxMode/box").value<box>();
            boxSettingsChanged = true;
            askForBoxesOptions* options = new askForBoxesOptions();
            options->start(&boxesSettings);
            options->exec();
        }
    }
}

void editSession::on_saveButton_clicked() {
    bool rename = false;
    qDebug() << "sessionSaved.core.name" << sessionSaved.core.name;
    qDebug() << "ui->lineEdit->text()" << ui->lineEdit->text();
    if(sessionSaved.core.name != ui->lineEdit->text()) {
        rename = true;
    }

    if((rename == true || boxSettingsChanged == true) && deleteSession == true) {
        qWarning() << "Renamed and deleted, aborting";
        this->close();
    }

    if(boxSettingsChanged == true) {
        QVariant variant = QVariant::fromValue(boxesSettings);
        settingsSession->setValue("boxMode/box", variant);
        settingsSession->sync();
    }

    if(rename == true) {
        QString oldName = sessionSaved.core.name;
        sessionSaved.core.name = ui->lineEdit->text();
        QVariant variant = QVariant::fromValue(sessionSaved);
        settingsSession->setValue("session", variant);
        settingsSession->sync();
        directories::sessionSaves.rename(oldName, ui->lineEdit->text());
    }

    if(deleteSession == true) {
        directories::sessionSaves.remove(sessionSaved.core.name);
    }

    emit refreshSessionsSignal();
    this->close();
}

void editSession::on_removeSession_toggled(bool checked) {
    deleteSession = checked;
}

void editSession::manageKeyboards() {
    QLineEdit* textEditToCheck = ui->lineEdit;
    if(textEditToCheck->underMouse() == true && textEditToCheck->hasFocus() == true) {
        keyboard* ereaderKeyboard = new keyboard();
        ereaderKeyboard->start(textEditToCheck);
        int y = this->pos().y();
        this->move(this->pos().x(), 0);
        ereaderKeyboard->exec();
        textEditToCheck->clearFocus();
        this->move(this->pos().x(), y);
        return void();
    }
}
