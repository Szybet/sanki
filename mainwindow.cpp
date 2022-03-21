#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

#include "libs/zip/src/zip.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    timer->start(1000);
    showTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CloseButton_clicked()
{
    delete ui;
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    ui->TimeLabel->setText(text);
}

void MainWindow::on_FileButton_clicked()
{
    QDir work_dir;
    work_dir.setPath(work_dir.currentPath());
    qDebug() << "work_dir" << work_dir.path();

    QDir deck_storage;
    deck_storage.setPath(work_dir.path() + "/deck_storage");
    qDebug() << "deck_storage" << deck_storage.path();
    if (deck_storage.exists() == false) {
         work_dir.mkdir("deck_storage");
         qDebug() << "created deck_storage";
    }

    QString zip_path = QFileDialog::getOpenFileName(this,
        tr("Choose an .apkg file"), ".", tr("Anki deck ( .apkg ) (*.apkg)"));
    qDebug() << "zip_path" << zip_path;

    QFile zip_file{zip_path};
    if (zip_file.exists()) {
        qDebug() << "zip exists";

        /*
        // libzip effors
        zip *zip_opened = zip_open(char_converted, 0, 0);
        int i;
        int buf_lenght;
        struct zip_file *zip_index;
        char buf[100];
        for (i = 0; i < zip_get_num_entries(zip_opened, 0); i++) {
            zip_index = zip_fopen_index(zip_opened, i, 0);
            buf_lenght = zip_fread(zip_index, buf, 100);
            qDebug() << "bufff" << buf_lenght;
        }
        */
        QDir new_deck;
        QFileInfo zip_file_info(zip_path);
        new_deck.setPath(deck_storage.path() + "/" + zip_file_info.baseName());
        qDebug() << "new_deck" << new_deck.path();
        deck_storage.mkdir(zip_file_info.baseName());

        // Converting to acceptable string
        QByteArray ba = zip_path.toLocal8Bit();
        const char *char_converted = ba.data();
        //
        int arg = 2; // why
        zip_extract(char_converted, new_deck.path().toLocal8Bit().data(), 0, &arg);

    }
}








