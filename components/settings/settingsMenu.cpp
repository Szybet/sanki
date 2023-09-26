#include "settingsMenu.h"
#include "ui_settingsMenu.h"

settingsMenu::settingsMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingsMenu)
{
    ui->setupUi(this);

    ui->pomodoroButton->setStyleSheet("Text-align: left");
    ui->settingsButton->setStyleSheet("Text-align: left");

}

settingsMenu::~settingsMenu()
{
    delete ui;
}
