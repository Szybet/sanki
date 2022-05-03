#include "card_view/mode_chooser.h"
#include "ui_mode_chooser.h"
#include "main_menu/mainwindow.h"

#include <QDebug>

mode_chooser::mode_chooser(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::mode_chooser)
{
    ui->setupUi(this);
}

mode_chooser::~mode_chooser()
{
    delete ui;
}


void mode_chooser::on_ButtonCRandom_clicked()
{
    mode = 1;
}


void mode_chooser::on_ButtonConfirm_clicked()
{

    if (mode > 0)
    {
        // parsing this variable could be done with this:
        // https://forum.qt.io/topic/15386/solved-accessing-a-parent-widget-s-variables/19
        // but its too complicated in my opinion
        emit set_mode(mode);
        this->close();
    }
}
