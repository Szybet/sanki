#include "widgget.h"
#include "ui_widgget.h"
#include <QWidget>

widgget::widgget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgget)
{
    ui->setupUi(this);
}

widgget::~widgget()
{
    delete ui;
}

/*
QWidget widgget::returnit()
{
    return ui;
}
*/
