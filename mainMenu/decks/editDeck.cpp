#include "mainMenu/decks/editDeck.h"
#include "ui_editDeck.h"
#include "global.h"
#include "components/other/keyboard.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QCursor>
#include <QProgressDialog>
#include <QSettings>

editDeck::editDeck(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::editDeck)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    ui->ButtonCancelEdit->setStyleSheet("font-size: 8pt");
    ui->ButtonRemoveDeck->setStyleSheet("font-size: 8pt");
    ui->ButtonSaveExit->setStyleSheet("font-size: 8pt");
    if(ereader) {
        ui->frame->setStyleSheet(".QFrame{background-color: white; border: 4px solid black; border-radius: 10px;}");
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &editDeck::manageKeyboards);
        timer->start(800);
    }
}

editDeck::~editDeck()
{
    delete ui;
}

void editDeck::updateWidget(QString string, int cursor)
{
    qDebug() << "Activated slot, QString: " << string << " int: " << cursor;

    // Adding cursor, this is so stupid
    QString string_with_cursor = string;
    if(cursor == 0)
    {
        if(string == "")
        {
            ui->lineeditDeckName->setText(" ");
        }
        string_with_cursor.insert(cursor, "|");
    } else {
        string_with_cursor.insert(cursor, "|");
    }

    ui->lineeditDeckName->setText(string_with_cursor);
    ui->lineeditDeckName->setCursorPosition(cursor);
}

void editDeck::updateDeck(QDir deckInfo)
{
    deckPath = deckInfo;
    ui->lineeditDeckName->setText(deckPath.dirName());
}

void editDeck::on_ButtonRemoveDeck_clicked()
{
    removeDeck = true;
}

void editDeck::on_ButtonCancelEdit_clicked()
{
    editDeck::close();
}

void editDeck::on_ButtonSaveExit_clicked()
{
    if(ui->lineeditDeckName->text() == deckPath.dirName()) {
        updatedName = false;
    }

    if(removeDeck == true and updatedName == true)
    {
        qWarning() << "Renamed and removed. try again with only one option";
    }

    if (updatedName == true) {
        qDebug() << "Dir path:" << deckPath.absolutePath();
        QString oldPath = directories::deckStorage.filePath(deckPath.dirName());
        QString newName = ui->lineeditDeckName->text();
        QString newPath = directories::deckStorage.filePath(newName);
        bool done = renameDir(deckPath, newName);
        if(done == false) {
            qWarning() << "Failed to rename deck";
        } else {
            qWarning() << "Starting renaming decks in sessions, don't exit or sessions may be corrupted";
            QProgressDialog progress("Renaming deck in sessions", "", 0, directories::sessionSaves.count(), this);
            progress.setWindowModality(Qt::WindowModal);
            progress.setCancelButton(nullptr); // Um?
            progress.show();

            if(ereader) {
                progress.setFixedWidth(ereaderVars::screenX);
                progress.move(0, progress.y());
            }

            foreach(QString file , directories::sessionSaves.entryList(QDir::NoDotAndDotDot | QDir::Files)) {
                qDebug() << "Session file:" << file;
                QSettings settings(directories::sessionSaves.filePath(file), QSettings::IniFormat);
                settings.sync();

                sessionStr session = settings.value("session").value<sessionStr>();
                if(session.core.name != file) {
                    qWarning() << "Failed to load session, sessions with this deck are corrupted...";
                    progress.close();
                    break;
                }
                bool found = false;
                for(int i = 0; i < session.core.deckPathList.count(); i++) {
                    qDebug() << "Iterating over decks:" << i << "current deck name choosed:" << session.core.deckPathList[i]  << "old name:" << oldPath;
                    if(session.core.deckPathList[i] == oldPath) {
                        qDebug() << "Found deck to replace name in session:" << session.core.name;
                        session.core.deckPathList[i] = newName;
                        found = true;
                    }
                }
                qDebug() << "Found status:" << found;

                QVariant toSave = QVariant::fromValue(session);
                if(toSave.isValid() == false || toSave.isNull() == true) {
                    qWarning() << "Failed to save session, sessions with this deck are corrupted...";
                    progress.close();
                    break;
                }
                settings.setValue("session", toSave);
                settings.sync();
                progress.setValue(progress.value() + 1);
            }
        }
        qDebug() << "Renamed directory from" << deckPath.absolutePath() << "to:" << ui->lineeditDeckName->text();
    }

    if (removeDeck == true)
    {
        qDebug() << "Removing dir: " << deckPath.path();
        deckPath.removeRecursively();
    }

    if(updatedName == true or removeDeck == true)
    {
        emit refreshDecksSignal();
        qDebug() << "Emitting refreshDecksSignal";
    }
    QApplication::processEvents();
    editDeck::close();
}

void editDeck::on_lineeditDeckName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    updatedName = true;
}

void editDeck::manageKeyboards() {
    QLineEdit* textEditToCheck = ui->lineeditDeckName;
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
