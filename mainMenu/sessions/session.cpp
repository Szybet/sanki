#include "session.h"
#include "ui_session.h"

session::session(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::session)
{
    ui->setupUi(this);
}

session::~session()
{
    delete ui;
}
