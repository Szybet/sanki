#include "mainwindow.h"
#include "deck.h"
#include "deck.cpp"

#include "ui_mainwindow.h"
#include "ui_deck.h"

#include <QTime>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "libs/zip/src/zip.h"

QDir deck_storage;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up timer for time showing
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    timer->start(1000);
    showTime();

    // Get current dir + deck storage paths
    QDir work_dir;
    work_dir.setPath(work_dir.currentPath());
    qDebug() << "work_dir" << work_dir.path();

    deck_storage.setPath(work_dir.path() + "/deck_storage");
    qDebug() << "deck_storage" << deck_storage.path();
    if (deck_storage.exists() == false) {
         work_dir.mkdir("deck_storage");
         qDebug() << "created deck_storage";
    }


    update_decks(deck_storage);
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


    QString zip_path = QFileDialog::getOpenFileName(this,
        tr("Choose an .apkg file"), ".", tr("Anki deck ( .apkg ) (*.apkg)"));
    qDebug() << "zip_path" << zip_path;

    QFile zip_file{zip_path};
    if (zip_file.exists()) {
        qDebug() << "zip exists";

        /*
        // libzip try
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

void MainWindow::update_decks(QDir deck_storage)
{

    QFileInfoList dir_list = deck_storage.QDir::entryInfoList(QDir::Dirs, QDir::Time);
    QLayout* scrollbar_layout = ui->scrollAreaWidgetContents->layout();

    //scrollbar_layout->addWidget(x);
    for (QFileInfo file_info: dir_list) {
        // Becouse of ".." and "."
        if (file_info.baseName() == "") {
            continue;
        }
        qDebug() << "file_info_dir" << file_info.baseName();
        deck* new_deck = new deck();
        new_deck->deck::set_deck_name(file_info.baseName());
        scrollbar_layout->addWidget(new_deck);
    }
}






