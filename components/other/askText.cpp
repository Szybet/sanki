#include "askText.h"
#include "global.h"
#include "ui_askText.h"
#include "components/other/keyboard.h"

#include <QTimer>

askText::askText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askText)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setResult(QDialog::Rejected);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &askText::manageKeyboards);
    timer->start(800);

    this->setFixedWidth(ereaderVars::screenX);

    ui->labelTitle->setVisible(false);
}

askText::~askText()
{
    delete ui;
}

void askText::on_buttonBox_accepted()
{
    this->setResult(QDialog::Accepted);
    this->done(QDialog::Accepted);
}

void askText::on_buttonBox_rejected()
{
    *textToSet = "";
    this->setResult(QDialog::Rejected);
    this->done(QDialog::Rejected);
}

void askText::manageKeyboards() {
    QLineEdit* textEditToCheck = ui->lineEdit;
    if((textEditToCheck->underMouse() == true && textEditToCheck->hasFocus() == true) || overwrite == true) {
        overwrite = false;
        keyboard* ereaderKeyboard = new keyboard(this);
        ereaderKeyboard->start(textEditToCheck);
        ereaderKeyboard->exec();
        textEditToCheck->clearFocus();
        *textToSet = textEditToCheck->text();

        return void();
    }
}

void askText::setTittle(QString text) {
    ui->labelTitle->setVisible(true);
    ui->labelTitle->setText(text);
}
