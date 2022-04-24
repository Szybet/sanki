#include "edit_deck.h"
#include "ui_edit_deck.h"
#include "mainwindow.h"
#include "globals.h"
#include "keyboard.h"

#include <QDebug>
#include <QApplication>
#include <QTimer>

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
    int x = (global_var::screen_x / 2) - ( this->width() / 2);
    int y = (global_var::screen_y / 3) - ( this->height() / 2);
    this->move(x, y);
    ui->lineEditDeckName->setCursorPosition(10);
}

edit_deck::~edit_deck()
{
    //delete ui;
}

void edit_deck::update_widget(QString string, int cursor)
{
         QString message = "Activated slot, QString: ";
         message.append(string);
         message.append(" int: ");
         message.append(QString::number(cursor));
         global_fun::log(message, "edit_deck.cpp", "update_widget");
         ui->lineEditDeckName->setText(string);
         ui->lineEditDeckName->setCursorPosition(cursor);
         if(string == "" and cursor == 0)
         {
             ui->lineEditDeckName->setText(" ");
             ui->lineEditDeckName->setText(string);
         }
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
    QDir dir = deck_info.dir();
    if (updated_name != "")
    {
        dir.QDir::rename(deck_info.baseName(), updated_name);
    }
     qDebug() << "GOING REMOVED";
    if (remove_deck == true)
    {
        if (updated_name == deck_info.baseName())
        {

            QDir deck_dir = deck_info.path() + "/" + deck_info.baseName();
            qDebug() << "REMOVED PATH" << deck_dir;
            qDebug() << "REMOVED";
            deck_dir.removeRecursively();
        } else {
            qDebug() << "NOT REMOVED";
        }
    }
    if (reset_deck == true)
    {
        // Reset the sql database in the future
    }

    // Update decks

    //MainWindow m(this);
    //emit m.remove_decks();
    //m.update_decks();

    emit refresh_decks_edit_signal();
    edit_deck::close();
}

// To improve here: make cursor bigger and after click move the cursor to the end, make it save the file and update decks
// + spacebar icon, !123 bold when clicked
void edit_deck::on_lineEditDeckName_cursorPositionChanged(int oldpos, int newpos)
{
    QString message = "cursor position changed to: ";
    message.append(QString::number(newpos));
    log_message.append(message);
    log_function.append("on_lineEditDeckName_cursorPositionChanged");
    // This here cannot provide variables
    QTimer::singleShot(0, this, SLOT(log()));
    if(first_open == false)
    {
        if(keyboard_opened == false)
        {
            if(newpos != 0)
            {

                log_message.append("keyboard open");
                log_function.append("on_lineEditDeckName_cursorPositionChanged");
                QTimer::singleShot(0, this, SLOT(log()));
                keyboard* keyboard_nameedit = new keyboard;
                keyboard_nameedit->cursor_main = newpos;
                keyboard_nameedit->main_string = ui->lineEditDeckName->text();
                keyboard_nameedit->edited_string = ui->lineEditDeckName->text();
                connect(keyboard_nameedit, SIGNAL(update_data(QString, int)), this, SLOT(update_widget(QString, int)));
                connect(keyboard_nameedit, SIGNAL(keyboard_closed()), this, SLOT(keyboard_closed()));
                keyboard_opened = true;
                keyboard_nameedit->exec();
            }
        }
    } else {
        log_function.append("on_lineEditDeckName_cursorPositionChanged");
        log_message.append("First open, skipping cursor change");
        QTimer::singleShot(0, this, SLOT(log()));
        ui->lineEditDeckName->setCursorPosition(0);
        first_open = false;
    }
}

void edit_deck::keyboard_closed()
{
    keyboard_opened = false;
}

void edit_deck::log()
{
    QString message = log_message.first();
    QString function = log_function.first();
    global_fun::log(message, log_file, function);
    log_message.removeFirst();
    log_function.removeFirst();
}
