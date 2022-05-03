#include "main_menu/mainwindow.h"
#include "components/toast.h"
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

    // Battery checking
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::battery_warning_timer);
    timer->start(15000);
    battery_warning_timer();

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
    connect(file_chooser_qdialog, SIGNAL(provide_file(QString)), this, SLOT(get_file(QString)));
    file_chooser_qdialog->exec();

    QFile zip_file{zip_file_path};
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
        QFileInfo zip_file_info(zip_file_path);
        new_deck.setPath(global_var::directories::deck_storage.path() + "/" + zip_file_info.baseName());
        qDebug() << "new_deck" << new_deck.path();
        global_var::directories::deck_storage.mkdir(zip_file_info.baseName());

        // Converting to acceptable string
        QByteArray ba = zip_file_path.toLocal8Bit();
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


void MainWindow::get_file(QString file)
{
    zip_file_path = file;

    QString message = "Slot activated, received: ";
    message.append(file);
    global_fun::log(message, log_file, "get_file");

}

void MainWindow::battery_warning_timer()
{
    global_fun::check_battery_level();
    if(global_var::batt_level_int < 30 and global_var::batt_level_int > 15)
    {
        toast* new_toast = new toast;
        new_toast->label_text = "Battery level is below 30%";
        new_toast->show_time_ms = 100000;
        new_toast->activate();
        new_toast->exec();
    } else if(global_var::batt_level_int < 15)
    {
        toast* new_toast = new toast;
        new_toast->label_text = "Battery level is below 15%";
        new_toast->show_time_ms = 100000;
        new_toast->activate();
        new_toast->exec();
    }
}
