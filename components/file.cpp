#include "file.h"
#include "ui_file.h"

#include <QIcon>

file::file(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::file)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("Text-align: left; font-size: 7pt; font-weight: normal; background: white");
}

file::~file()
{
    delete ui;
}

void file::set_button_look(QString text, QIcon icon)
{
    ui->pushButton->setText(text);
    ui->pushButton->setIcon(icon);
}

void file::remove_bold()
{
    if(ignore_remove_bold_signal == true)
    {
        ignore_remove_bold_signal = false;
    } else {
        if(is_directory == true)
        {
            ui->pushButton->setText(ui->pushButton->text().remove(" →"));
        }

        // this resets
        ui->pushButton->setStyleSheet("Text-align: left; font-size: 7pt; font-weight: normal; background: white");
    }
}

void file::on_pushButton_clicked()
{
    ignore_remove_bold_signal = true;

    emit im_clicked(ui->pushButton->text());
    if(is_directory == true)
    {
        ui->pushButton->setText(ui->pushButton->text() + " →");
    }

    // this resets
    ui->pushButton->setStyleSheet("Text-align: left; font-size: 7pt; font-weight: bold; background: lightGrey");

}

