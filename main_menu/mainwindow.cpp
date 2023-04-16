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
    // Dont start it here becouse it will be fullscreen for some reason

    // Setup default status bar
    status_bar_main_menu();


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

    central_layout->addWidget(decks);
    emit update_decks();
    qDebug() << "update_decks emitet";
}

void MainWindow::deck_play_show(QDir dir)
{
    // This here goes to card_view thing, going to play
    QString message = "Dir choosed to play: ";
    message.append(dir.path());
    debugLog(message, log_file, "deck_play_show");

    // this was propably causing problems
    //int mode = choose_mode->exec();

    mode_chooser* choose_mode = new mode_chooser;
    connect(choose_mode, SIGNAL(set_mode(int)), this, SLOT(get_mode(int)));
    choose_mode->exec();

    // status bar for this
    emit close_status_bar();
    status_bar* status_bar_up = new status_bar();
    status_bar_up->option_button_enabled(false);
    connect(this, SIGNAL(close_status_bar()), status_bar_up, SLOT(close()));
    connect(status_bar_up, SIGNAL(close_button_signal()), this, SLOT(return_to_mainwindow()));
    ui->gridStatus->addWidget(status_bar_up);

    emit clear_mainwidget();
    QLayout* central_layout = ui->centralwidget->layout();
    DeckPlay* play_deck = new DeckPlay();
    play_deck->update(dir, mode);
    connect(this, SIGNAL(clear_mainwidget()), play_deck, SLOT(close()));
    central_layout->addWidget(play_deck);
}

void MainWindow::FileButton()
{
    // Dont get confused, this is a slot activated from status bar
    file_chooser* file_chooser_qdialog = new file_chooser;
    file_chooser_qdialog->start_path = directories::work_dir.path();
    file_chooser_qdialog->update_files();
    connect(file_chooser_qdialog, SIGNAL(provide_file(QString)), this, SLOT(get_file(QString)));
    file_chooser_qdialog->exec();

    QFile zip_file{zip_file_path};
    if (zip_file.exists()) {
        debugLog("zip to be added exists", log_file, "FileButton");

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
        new_deck.setPath(directories::deck_storage.path() + "/" + zip_file_info.baseName());

        QString message = "new deck path: ";
        message.append(new_deck.path());
        debugLog(message, log_file, "FileButton");

        directories::deck_storage.mkdir(zip_file_info.baseName());

        // Converting to acceptable string
        QByteArray ba = zip_file_path.toLocal8Bit();
        const char *char_converted = ba.data();
        int arg = 2; // why
        zip_extract(char_converted, new_deck.path().toLocal8Bit().data(), 0, &arg);
    }
    // Update decks
    emit update_decks();
    debugLog("update_decks emitet", log_file, "FileButton");
}

void MainWindow::battery_warning_timer()
{
    check_battery_level();
    if(batt_level_int < 30 and batt_level_int > 15)
    {
        toast* new_toast = new toast;
        new_toast->label_text = "Battery level is below 30%";
        new_toast->show_time_ms = 100000;
        new_toast->activate();
        new_toast->exec();
    } else if(batt_level_int < 15)
    {
        toast* new_toast = new toast;
        new_toast->label_text = "Battery level is below 15%";
        new_toast->show_time_ms = 100000;
        new_toast->activate();
        new_toast->exec();
    }
}

void MainWindow::get_file(QString file)
{
    zip_file_path = file;
    QString message = "Slot activated, received: ";
    message.append(file);
    debugLog(message, log_file, "get_file");
}

void MainWindow::get_mode(int mode_slot)
{
    QString message = "Slot activated, received: ";
    message.append(mode_slot);
    debugLog(message, log_file, "get_mode");
    mode = mode_slot;
}

void MainWindow::status_bar_main_menu()
{
    emit close_status_bar();
    status_bar* status_bar_up = new status_bar();
    QIcon file_chooser_icon = QIcon(":/icons/folder.png");
    status_bar_up->option_button_set("Add deck", file_chooser_icon);
    connect(this, SIGNAL(close_status_bar()), status_bar_up, SLOT(close()));
    connect(status_bar_up, SIGNAL(option_button_signal()), this, SLOT(FileButton()));
    connect(status_bar_up, SIGNAL(close_button_signal()), this, SLOT(close()));
    ui->gridStatus->addWidget(status_bar_up);

}

void MainWindow::return_to_mainwindow()
{
    emit clear_mainwidget();
    deck_scroll_bar_show();
    status_bar_main_menu();
}
