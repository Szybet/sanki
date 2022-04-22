#include "decks_scroll_bar.h"
#include "ui_decks_scroll_bar.h"
#include "mainwindow.h"
#include "deck.h"
#include "ui_mainwindow.h"
#include "ui_deck.h"
#include "status_bar.h"
#include "globals.h"

#include <QTime>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QScrollBar>
#include <QSpacerItem>

decks_scroll_bar::decks_scroll_bar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::decks_scroll_bar)
{
    ui->setupUi(this);

    if (deck_storage.exists() == false) {
         work_dir.mkdir("deck_storage");
         qDebug() << "created deck_storage";
    }

    // This could be editable in settings
    ui->DeckScrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");
}

decks_scroll_bar::~decks_scroll_bar()
{
    delete ui;
}

void decks_scroll_bar::update_decks()
{
    qDebug() << "UPDATE";
    emit remove_decks();

    QFileInfoList dir_list = deck_storage.QDir::entryInfoList(QDir::Dirs, QDir::Time);
    QGridLayout* scrollbar_layout = ui->DeckGrid;

    int row = 0; // horizontal
    int column = 0; // vertical
    for (QFileInfo file_info: dir_list) {
        // Becouse of ".." and "."
        if (file_info.baseName() == "") {
            continue;
        }
        qDebug() << "file_info_dir" << file_info.baseName();
        deck* new_deck = new deck();
        new_deck->deck::set_deck_name(file_info.baseName());
        new_deck->deck_info = file_info;
        // addWidget(QWidget *widget, int row, int column, Qt::Alignment alignment = Qt::Alignment())
        connect(this, SIGNAL(remove_decks()), new_deck, SLOT());
        connect(new_deck, SIGNAL(refresh_decks_signal()), this, SLOT(update_decks()));
        connect(new_deck, SIGNAL(play_deck(QDir)), this, SLOT(play_deck_slott(QDir)));
        scrollbar_layout->addWidget(new_deck, row, column);
        column = column + 1;
        if (column == 2)
        {
            column = 0;
            row = row + 1;
        }

    }
}

void decks_scroll_bar::play_deck_slott(QDir dir)
{
    qDebug() << "DECKPLAY - SCROLL";
    emit play_deck_signal(dir);
}
