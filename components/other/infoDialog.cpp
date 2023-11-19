#include "infoDialog.h"
#include "ui_infoDialog.h"

infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setLineWrapMode(QTextEdit::WidgetWidth);
    ui->textBrowser->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
}

infoDialog::~infoDialog()
{
    delete ui;
}

void infoDialog::on_pushButton_clicked()
{
    this->close();
}

void infoDialog::setText(QString text) {
    ui->textBrowser->setText(text);
    QApplication::processEvents();
    // To make it fit...
    if(ui->textBrowser->height() < ui->textBrowser->document()->size().height()) {
        ui->textBrowser->setFixedHeight(ui->textBrowser->document()->size().height() + 20);
    }
}
