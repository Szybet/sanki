#include "main_menu/mainwindow.h"
#include "main_menu/deck.h"
#include "main_menu/deck.cpp"
#include "ui_mainwindow.h"
#include "ui_deck.h"
#include "components/status_bar.h"
#include "main_menu/decks_scroll_bar.h"
#include "globals.h"
#include "card_view/mode_chooser.h"
#include "zip.h"
#include "components/file_chooser.h"

#include <QTime>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup status bar
    status_bar* status_bar_up = new status_bar();
    QIcon file_chooser_icon = QIcon(":/icons/folder.png");
    status_bar_up->option_button_set("Add deck", file_chooser_icon);
    connect(status_bar_up, SIGNAL(option_button_signal()), this, SLOT(on_FileButton_clicked()));
    connect(status_bar_up, SIGNAL(close_button_signal()), this, SLOT(exit_app()));
    ui->gridStatus->addWidget(status_bar_up);


    // show scroll bar
    deck_scroll_bar_show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deck_scroll_bar_show()
{
    decks_scroll_bar* decks = new decks_scroll_bar;
    auto central_layout = ui->centralwidget->layout();
    connect(this, SIGNAL(update_decks()), decks, SLOT(update_decks()));
    connect(decks, SIGNAL(play_deck_signal(QDir)), this, SLOT(deck_play_show(QDir)));
    connect(this, SIGNAL(clear_mainwidget()), decks, SLOT(deleteLater()));
    // Something is wrong the passing an argument with signal and slots
    central_layout->addWidget(decks);
    emit update_decks();
}

void MainWindow::deck_play_show(QDir dir)
{
    qDebug() << "DECKPLAY - MAIN" << dir;
    //mode_chooser* choose_mode = new mode_chooser;
    //int mode = choose_mode->exec();

    emit clear_mainwidget();
    auto central_layout = ui->centralwidget->layout();
    DeckPlay* play_deck = new DeckPlay();
    play_deck->update(dir, 1);
    connect(this, SIGNAL(clear_mainwidget()), play_deck, SLOT(deleteLater()));
    central_layout->addWidget(play_deck);
}

void MainWindow::on_CloseButton_clicked()
{
    exit_app();
}

void MainWindow::on_FileButton_clicked()
{
    file_chooser* file_chooser_qdialog = new file_chooser;

    file_chooser_qdialog->update_files();

    auto idk = file_chooser_qdialog->exec();

    qDebug() << "LOG: idk from file chooser" << idk;


    QString zip_path = "test it is";
    QFile zip_file{zip_path};
    if (zip_file.exists()) {
        qDebug() << "zip exists";


        // libzip try
        /*
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
        new_deck.setPath(global_var::directories::deck_storage.path() + "/" + zip_file_info.baseName());
        qDebug() << "new_deck" << new_deck.path();
        global_var::directories::deck_storage.mkdir(zip_file_info.baseName());

        // Converting to acceptable string
        QByteArray ba = zip_path.toLocal8Bit();
        const char *char_converted = ba.data();
        //
        int arg = 2; // why
        zip_extract(char_converted, new_deck.path().toLocal8Bit().data(), 0, &arg);


    }
    // Update decks
    emit update_decks();

}

void MainWindow::exit_app()
{
    QApplication::closeAllWindows();
}




