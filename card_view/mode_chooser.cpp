#include "card_view/mode_chooser.h"
#include "ui_mode_chooser.h"

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
        qDebug() << "DECKPLAY - mode_emit" << mode;
        this->done(mode);
        this->close();
    }
}
