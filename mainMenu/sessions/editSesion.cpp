#include "editSession.h"
#include "ui_editSession.h"

editSession::editSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editSession)
{
    ui->setupUi(this);
}

editSession::~editSession()
{
    delete ui;
}
