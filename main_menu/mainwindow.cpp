#include "main_menu/mainwindow.h"
#include "components/toast.h"
#include "main_menu/deck.h"
#include "main_menu/deck.cpp"
#include "ui_mainwindow.h"
#include "ui_deck.h"
#include "components/status_bar.h"
#include "main_menu/decks_scroll_bar.h"
#include "globals.h"
#include "cardView/modeChooser.h"
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
    if(ereader) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::battery_warning_timer);
        timer->start(15000);
    }

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
    connect(decks, SIGNAL(play_deck_signal(QDir)), this, SLOT(deckPlay_show(QDir)));
    connect(this, SIGNAL(clear_mainwidget()), decks, SLOT(deleteLater()));

    central_layout->addWidget(decks);
    emit update_decks();
    qDebug() << "update_decks emitet";
}

void MainWindow::deckPlay_show(QDir dir)
{
    // This here goes to cardView thing, going to play
    qDebug() << "Dir choosed to play:" << dir.path();

    // this was propably causing problems
    //int mode = chooseMode->exec();

    modeChooser* chooseMode = new modeChooser;
    connect(chooseMode, SIGNAL(setMode(DeckModes)), this, SLOT(getMode(DeckModes)));
    int code = chooseMode->exec();
    qDebug() << "chooseMode dialog return value is:" << code;
    if(code == QDialog::Accepted) {
        // status bar for this
        emit close_status_bar();
        status_bar* status_bar_up = new status_bar();
        status_bar_up->option_button_enabled(false);
        connect(this, SIGNAL(close_status_bar()), status_bar_up, SLOT(close()));
        connect(status_bar_up, SIGNAL(close_button_signal()), this, SLOT(return_to_mainwindow()));
        ui->gridStatus->addWidget(status_bar_up);

        emit clear_mainwidget();
        QLayout* central_layout = ui->centralwidget->layout();
        DeckPlay* playDeck = new DeckPlay();
        playDeck->update(dir, mode);
        connect(this, SIGNAL(clear_mainwidget()), playDeck, SLOT(close()));
        central_layout->addWidget(playDeck);
    }
}

void MainWindow::FileButton()
{
    // Dont get confused, this is a slot activated from status bar
    if(ereader) {
        // TODO: select file type
        file_chooser* file_chooser_qdialog = new file_chooser;
        file_chooser_qdialog->start_path = directories::deckSelect.path();
        file_chooser_qdialog->update_files();
        connect(file_chooser_qdialog, SIGNAL(provide_file(QString)), this, SLOT(get_file(QString)));
        file_chooser_qdialog->exec();
    } else if(pc) {
        zipFilePath = QFileDialog::getOpenFileName(this,
                                                   tr("Select anki deck"), directories::deckSelect.path(), tr("Anki Files (*.zip *.apkg)"));
    }

    QFile zip_file{zipFilePath};
    if (zip_file.exists()) {
        qDebug() << "zip to be added exists";

        QDir newDeck;
        QFileInfo zip_file_info(zipFilePath);
        newDeck.setPath(directories::deckStorage.path() + "/" + zip_file_info.baseName());

        qDebug() << "new deck path: " << newDeck.path();

        directories::deckStorage.mkdir(zip_file_info.baseName());

        // Converting to acceptable string
        QByteArray ba = zipFilePath.toLocal8Bit();
        const char *char_converted = ba.data();
        int arg = 2; // why
        zip_extract(char_converted, newDeck.path().toLocal8Bit().data(), 0, &arg);
    }
    // Update decks
    emit update_decks();
    qDebug() << "update_decks emitted";
}

void MainWindow::battery_warning_timer()
{
    check_battery_level();
    if(ereaderVars::batt_level_int < 30 and ereaderVars::batt_level_int > 15)
    {
        toast* new_toast = new toast;
        new_toast->label_text = "Battery level is below 30%";
        new_toast->show_time_ms = 100000;
        new_toast->activate();
        new_toast->exec();
    } else if(ereaderVars::batt_level_int < 15)
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
    zipFilePath = file;
    qDebug() << "Slot activated, received:" << file;
}

void MainWindow::getMode(DeckModes modeSelected)
{
    qDebug() << "Slot activated, received: " << modeSelected;
    mode = modeSelected;
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
