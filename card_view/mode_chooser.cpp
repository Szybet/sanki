#include "card_view/mode_chooser.h"
#include "ui_mode_chooser.h"
#include "main_menu/mainwindow.h"

#include <QDebug>

mode_chooser::mode_chooser(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::mode_chooser)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("border: 4px solid back;");

    //ui->ButtonCRandom->setStyleSheet("QRadioButton::indicator::unchecked{color: #184880; width: 10px; height: 10px; background: white; border-width: 2px; border-style: solid; border-radius: 7px;}; QRadioButton::indicator::checked{color: #184880; width: 10px; height: 10px; background: white; border-width: 2px; border-style: solid; border-radius: 7px;}");
    //ui->ButtonCRandom->setStyleSheet("QRadioButton::indicator:checked{color: black; background: black; border-width: 2px; border-style: solid; border-radius: 7px; border-color: white;}");
    //ui->ButtonCRandom->setStyleSheet("QRadioButton::indicator::unchecked {image: url(:/icons/radio_button_unchecked.png)}; QRadioButton::indicator::checked {image: url(:/icons/radio_button_checked.png)}");
    // Nothing works, so this:
    ui->ButtonCRandom->setStyleSheet("QRadioButton::indicator{width: 0px; height: 0px;}");
    ui->ButtonCRandom->setIcon(QIcon(":/icons/radio_button_unchecked.png"));
    ui->ButtonCRandom->setIconSize(QSize(33, 33));


    ui->ButtonRandomNR->setStyleSheet("QRadioButton::indicator{width: 0px; height: 0px;}");
    ui->ButtonRandomNR->setIcon(QIcon(":/icons/radio_button_unchecked.png"));
    ui->ButtonRandomNR->setIconSize(QSize(33, 33));
}

mode_chooser::~mode_chooser()
{
    delete ui;
}


void mode_chooser::on_ButtonCRandom_clicked(bool checked)
{
    if(checked == true)
    {
        mode = 1;
        ui->ButtonCRandom->setIcon(QIcon(":/icons/radio_button_checked.png"));

        // this needs to be done better
        ui->ButtonRandomNR->setIcon(QIcon(":/icons/radio_button_unchecked.png"));

    } else {
        mode = 0;
        ui->ButtonCRandom->setIcon(QIcon(":/icons/radio_button_unchecked.png"));
    }
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

void mode_chooser::on_ButtonRandomNR_clicked(bool checked)
{
    if(checked == true)
    {
        mode = 2;
        ui->ButtonRandomNR->setIcon(QIcon(":/icons/radio_button_checked.png"));
        // this needs to be done better
        ui->ButtonCRandom->setIcon(QIcon(":/icons/radio_button_unchecked.png"));


    } else {
        mode = 0;
        ui->ButtonRandomNR->setIcon(QIcon(":/icons/radio_button_unchecked.png"));
    }
}
