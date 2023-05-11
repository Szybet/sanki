#include "cardView/modeOptions.h"
#include "ui_modeOptions.h"
#include "global.h"

#include <QDebug>

modeChooser::modeChooser(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::modeChooser)
{
    ui->setupUi(this);

    if(ereader) ui->groupBox->setStyleSheet("border: 4px solid back;");
    ui->ButtonConfirm->setEnabled(false);

    // To check if the dialog was closed on PC with close button
    this->setResult(QDialog::Rejected);
}

modeChooser::~modeChooser()
{
    delete ui;
}

void modeChooser::on_ButtonConfirm_clicked()
{
    emit setMode(mode);
    this->setResult(QDialog::Accepted);
    this->deleteLater();
    this->done(QDialog::Accepted);
}

void modeChooser::modeManager(DeckModes newMode) {
    ui->ButtonConfirm->setEnabled(true);
    ui->ButtonCRandom->setChecked(false);
    ui->ButtonRandomNR->setChecked(false);

    if(newMode == RandomisedNoRepeating) {
        ui->ButtonRandomNR->setChecked(true);
    } else if(newMode == CompletlyRandomised) {
        ui->ButtonCRandom->setChecked(true);
    } else if(newMode == Boxes) {
        ui->ButtonBoxes->setChecked(true);
    }

    mode = newMode;
}

void modeChooser::on_ButtonRandomNR_clicked()
{
    modeManager(RandomisedNoRepeating);
}

void modeChooser::on_ButtonCRandom_clicked()
{
    modeManager(CompletlyRandomised);
}

void modeChooser::on_ButtonBoxes_clicked()
{
    modeManager(Boxes);
}


void modeChooser::on_boxesInfoButton_clicked()
{
    QString info = "This is the closest to the Anki experience<br><br>"
                   "Cards are put in boxes, and depending on the button value ( good, bad... etc ) it is moved to a diffrent box<br><br>"
        "this determines how often the card is shown";
    qInfo() << info;
}


void modeChooser::on_CRInfoButton_clicked()
{
    qInfo() << "Completly randomly choosed cards are shown. There is no making sure that they don't repeat often";
}
