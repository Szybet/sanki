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
    }

    // this->adjustSize();
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
        qCritical() << "Renamed and removed. try again with only one option";
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

            foreach(QString file , directories::sessionSaves.entryList(QDir::NoDotAndDotDot | QDir::Files)) {
                qDebug() << "Session file:" << file;
                QSettings settings(directories::sessionSaves.filePath(file), QSettings::IniFormat);
                settings.sync();

                sessionStr session = settings.value("session").value<sessionStr>();
                if(session.core.name != file) {
                    qCritical() << "Failed to load session, sessions with this deck are corrupted...";
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
                    qCritical() << "Failed to save session, sessions with this deck are corrupted...";
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

void editDeck::on_lineeditDeckName_cursorPositionChanged(int oldpos, int newpos)
{
    if(ereader) {
        qDebug() << "cursor position changed to: " << newpos << "from:" << oldpos;
        if(firstOpen == false)
        {
            if(keyboardOpened == false)
            {
                if(newpos != 0)
                {
                    qDebug() << "Keyboard open";
                    QTimer::singleShot(0, this, SLOT(debugLog()));
                    keyboard* keyboard_nameedit = new keyboard;
                    keyboard_nameedit->cursor_main = newpos;
                    keyboard_nameedit->main_string = ui->lineeditDeckName->text();
                    keyboard_nameedit->edited_string = ui->lineeditDeckName->text();
                    connect(keyboard_nameedit, SIGNAL(update_data(QString, int)), this, SLOT(updateWidget(QString, int)));
                    connect(keyboard_nameedit, SIGNAL(keyboardClosed(bool)), this, SLOT(keyboardClosed(bool)));
                    keyboardOpened = true;
                    updateWidget(ui->lineeditDeckName->text(), ui->lineeditDeckName->cursorPosition()); // to create the cursor
                    keyboard_nameedit->exec();
                }
            }
        } else {
            qDebug() << "First open, skipping cursor change";

            ui->lineeditDeckName->setCursorPosition(0);
            firstOpen = false;
        }
    }
}

void editDeck::keyboardClosed(bool updateName)
{
    if(updateName == true)
    {
        updatedName = true;
    }
    ui->lineeditDeckName->setText(ui->lineeditDeckName->text().remove("|"));
    ui->lineeditDeckName->setCursorPosition(0);
    keyboardOpened = false;
}

void editDeck::on_lineeditDeckName_selectionChanged()
{
    if(ereader) {
        ui->lineeditDeckName->setSelection(0, 0);
    }
}

void editDeck::on_lineeditDeckName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    updatedName = true;
}

