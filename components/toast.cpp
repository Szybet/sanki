#include "components/toast.h"
#include "ui_toast.h"

#include "QTimer"
#include "globals.h"

toast::toast(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::toast)
{
    ui->setupUi(this);
}

toast::~toast()
{
    delete ui;
}

void toast::activate()
{
    ui->text->setText(label_text);
    QTimer::singleShot(show_time_ms, this, SLOT(close()));

    // This needs to be here becouse selectAll()
    ui->pushButton->setStyleSheet("font-size: 8pt");
    ui->text->setStyleSheet("font-size: 8pt");
    ui->frame->setStyleSheet(".QFrame{background-color: white; border: 4px solid black; border-radius: 10px;}");

    // Align at center
    ui->text->selectAll();
    ui->text->setAlignment(Qt::AlignCenter);
    QTextCursor c = ui->text->textCursor();
    c.setPosition(0);
    c.setPosition(0, QTextCursor::KeepAnchor);
    ui->text->setTextCursor(c);
}

void toast::on_pushButton_clicked()
{
    this->close();
}

