#include "file.h"
#include "ui_file.h"

#include <QIcon>

file::file(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::file)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

file::~file()
{
    delete ui;
}

void file::start(bool isDirectoryProvided, QString text, QIcon icon)
{
    isDirectory = isDirectoryProvided;
    ui->pushButton->setText(text);
    ui->pushButton->setIcon(icon);

    ui->pushButton->setStyleSheet("Text-align: left; font-size: 7pt; font-weight: normal; background: white");
}

void file::removeBold()
{
    if(ignoreRemoveBoldSignal == true)
    {
        ignoreRemoveBoldSignal = false;
    } else {
        if(isDirectory == true)
        {
            ui->pushButton->setText(ui->pushButton->text().remove(" →"));
        }
        // this resets
        ui->pushButton->setStyleSheet("Text-align: left; font-size: 7pt; font-weight: normal; background: white");
    }
}

void file::on_pushButton_clicked()
{
    if(isDirectory == true)
    {
        // this checks if its clicked, if yes then enter the dir
        if(ui->pushButton->text().contains(" →") == true)
        {
            emit enterDirectory();
        }
    }
    ignoreRemoveBoldSignal = true;

    emit fileClicked(ui->pushButton->text());
    if(isDirectory == true)
    {
        ui->pushButton->setText(ui->pushButton->text() + " →");
    }

    // this resets
    ui->pushButton->setStyleSheet("Text-align: left; font-size: 7pt; font-weight: bold; background: lightGrey");
}

