#include "status_bar.h"
#include "ui_status_bar.h"

status_bar::status_bar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::status_bar)
{
    ui->setupUi(this);
}

status_bar::~status_bar()
{
    delete ui;
}
