#include "keyboard.h"
#include "ui_keyboard.h"
#include "globals.h"

keyboard::keyboard(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::keyboard)
{
    ui->setupUi(this);

    int y = (global_var::screen_y / 2);
    this->move(0, y);
    this->setMinimumSize(global_var::screen_x, y);
    this->adjustSize();

    ui->lineEdit->setVisible(false);
}

keyboard::~keyboard()
{
    delete ui;
}

void keyboard::update_string(QString new_string)
{
    edited_string.insert(cursor_main, new_string);
    global_fun::log("Emiting update_data", "keyboard.cpp", "update_string()");
    emit update_data(edited_string, cursor_main);
}

void keyboard::on_Button_q_clicked()
{
    update_string("q");
}

