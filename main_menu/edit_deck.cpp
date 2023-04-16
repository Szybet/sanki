#include "main_menu/edit_deck.h"
#include "ui_edit_deck.h"
#include "globals.h"
#include "components/keyboard.h"
#include "components/toast.h"

#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QCursor>

edit_deck::edit_deck(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::edit_deck)
{
    ui->setupUi(this);
    ui->ButtonCancelEdit->setStyleSheet("font-size: 8pt");
    ui->ButtonRemoveDeck->setStyleSheet("font-size: 8pt");
    ui->ButtonReset->setStyleSheet("font-size: 8pt");
    ui->ButtonSaveExit->setStyleSheet("font-size: 8pt");
    ui->frame->setStyleSheet(".QFrame{background-color: white; border: 4px solid black; border-radius: 10px;}");


    this->adjustSize();
    int x = (screen_x / 2) - ( this->width() / 2);
    int y = (screen_y / 3) - ( this->height() / 2);
    this->move(x, y);
    ui->lineEditDeckName->setCursorPosition(10);

    /* doesn't work at all
    QPixmap pixmap = QPixmap(":cursor");
    QCursor cursor = QCursor(pixmap, 0, 0);
    QGuiApplication::setOverrideCursor(QCursor(cursor));
    */
}

edit_deck::~edit_deck()
{
    delete ui;
}

void edit_deck::update_widget(QString string, int cursor)
{
         QString message = "Activated slot, QString: ";
         message.append(string);
         message.append(" int: ");
         message.append(QString::number(cursor));
         debugLog(message, "edit_deck.cpp", "update_widget");

         // Adding cursor, this is so stupid
         QString string_with_cursor = string;
         if(cursor == 0)
         {
             if(string == "")
             {
                 ui->lineEditDeckName->setText(" ");
             }
             string_with_cursor.insert(cursor, "|");
         } else {
             string_with_cursor.insert(cursor, "|");
         }

         ui->lineEditDeckName->setText(string_with_cursor);
         ui->lineEditDeckName->setCursorPosition(cursor);
}

void edit_deck::update_deck()
{
    QString deck_name = deck_info.baseName();
    ui->lineEditDeckName->setText(deck_name);
}

void edit_deck::on_ButtonRemoveDeck_clicked()
{
    remove_deck = true;
}


void edit_deck::on_ButtonReset_clicked()
{
    reset_deck = true;
}

void edit_deck::on_ButtonCancelEdit_clicked()
{
    edit_deck::close();
}


void edit_deck::on_ButtonSaveExit_clicked()
{
    QString log_function = "on_ButtonSaveExit_clicked()";

    if(remove_deck == true and updated_name == true)
    {
        // show toast that this is weird, not removing
        toast* new_toast = new toast;
        new_toast->label_text = "ERROR\n renamed and removed. try again with only one option";
        new_toast->show_time_ms = 100000;
        new_toast->activate();
        new_toast->exec();
        edit_deck::close();
    }

    if (updated_name == true)
    {
        QDir dir = deck_info.absoluteDir();
        dir.QDir::rename(deck_info.baseName(), ui->lineEditDeckName->text());

        QString message = "renamed directory from ";
        message.append(deck_info.baseName());
        message.append(" to: ");
        message.append(ui->lineEditDeckName->text());
        debugLog(message, log_file, log_function);
    }

    if (remove_deck == true)
    {
        // why this works, why
        QDir remove_dir = deck_info.path() + "/" + deck_info.baseName();

        QString message = "removing dir: ";
        message.append(remove_dir.path());
        debugLog(message, log_file, log_function);

        remove_dir.removeRecursively();
    }
    if (reset_deck == true)
    {
        // Reset the sql database in the future
    }

    if(updated_name == true or remove_deck == true or reset_deck == true)
    {
        emit refresh_decks_edit_signal();
        debugLog("emiting refresh_decks_edit_signal", log_file, log_function);
    }
    edit_deck::close();
}

void edit_deck::on_lineEditDeckName_cursorPositionChanged(int oldpos, int newpos)
{
    QString message = "cursor position changed to: ";
    message.append(QString::number(newpos));
    log_message.append(message);
    log_function.append("on_lineEditDeckName_cursorPositionChanged");
    // This here cannot provide variables
    QTimer::singleShot(0, this, SLOT(debugLog()));
    if(first_open == false)
    {
        if(keyboard_opened == false)
        {
            if(newpos != 0)
            {

                log_message.append("keyboard open");
                log_function.append("on_lineEditDeckName_cursorPositionChanged");
                QTimer::singleShot(0, this, SLOT(debugLog()));
                keyboard* keyboard_nameedit = new keyboard;
                keyboard_nameedit->cursor_main = newpos;
                keyboard_nameedit->main_string = ui->lineEditDeckName->text();
                keyboard_nameedit->edited_string = ui->lineEditDeckName->text();
                connect(keyboard_nameedit, SIGNAL(update_data(QString, int)), this, SLOT(update_widget(QString, int)));
                connect(keyboard_nameedit, SIGNAL(keyboard_closed(bool)), this, SLOT(keyboard_closed(bool)));
                keyboard_opened = true;
                update_widget(ui->lineEditDeckName->text(), ui->lineEditDeckName->cursorPosition()); // to create the cursor
                keyboard_nameedit->exec();
            }
        }
    } else {
        log_function.append("on_lineEditDeckName_cursorPositionChanged");
        log_message.append("First open, skipping cursor change");
        QTimer::singleShot(0, this, SLOT(debugLog()));
        ui->lineEditDeckName->setCursorPosition(0);
        first_open = false;
    }
}

void edit_deck::keyboard_closed(bool update_name)
{
    if(update_name == true)
    {
        updated_name = true;
    }
    ui->lineEditDeckName->setText(ui->lineEditDeckName->text().remove("|"));
    ui->lineEditDeckName->setCursorPosition(0);
    keyboard_opened = false;
}

void edit_deck::on_lineEditDeckName_selectionChanged()
{
    ui->lineEditDeckName->setSelection(0, 0);
}

