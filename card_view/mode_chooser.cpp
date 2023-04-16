#include "card_view/mode_chooser.h"
#include "ui_mode_chooser.h"
#include "globals.h"

#include <QDebug>

mode_chooser::mode_chooser(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::mode_chooser)
{
    ui->setupUi(this);

    if(ereader) ui->groupBox->setStyleSheet("border: 4px solid back;");
    ui->ButtonConfirm->setEnabled(false);

    // To check if the dialog was closed on PC with close button
    this->setResult(QDialog::Rejected);
}

mode_chooser::~mode_chooser()
{
    delete ui;
}

void mode_chooser::on_ButtonConfirm_clicked()
{
    emit setMode(mode);
    this->setResult(QDialog::Accepted);

    this->deleteLater();
    this->done(QDialog::Accepted);
}

void mode_chooser::modeManager(DeckModes newMode) {
    ui->ButtonConfirm->setEnabled(true);

    ui->ButtonCRandom->setChecked(false);
    ui->ButtonRandomNR->setChecked(false);

    if(newMode == RandomisedNoRepeating) {
        ui->ButtonRandomNR->setChecked(true);
    } else if(newMode == CompletlyRandomised) {
        ui->ButtonCRandom->setChecked(true);
    }

    mode = newMode;
}

void mode_chooser::on_ButtonRandomNR_clicked()
{
    modeManager(RandomisedNoRepeating);
}

void mode_chooser::on_ButtonCRandom_clicked()
{
    modeManager(CompletlyRandomised);
}
