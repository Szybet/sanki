#include "main_menu/decks_scroll_bar.h"
#include "ui_decks_scroll_bar.h"
#include "main_menu/deck.h"
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
    qDebug() << "update_decks slot called";
    emit remove_decks();

    QFileInfoList dir_list = directories::deckStorage.QDir::entryInfoList(QDir::Dirs, QDir::Time);
    for (QFileInfo file_info: dir_list) {
        QString fileName = file_info.baseName();
        if (fileName == "") {
            continue;
        }
        qDebug() << "Dir found:" << fileName;
    }

    QGridLayout* scrollbar_layout = ui->DeckGrid;

    int row = 0; // horizontal
    int column = 0; // vertical
    for (QFileInfo file_info: dir_list) {
        QString fileName = file_info.baseName();
        // Becouse of ".." and "."
        if (fileName == "") {
            continue;
        }
        deck* newDeck = new deck(this);
        newDeck->set_deck_name(fileName);
        newDeck->deck_info = file_info;
        // addWidget(QWidget *widget, int row, int column, Qt::Alignment alignment = Qt::Alignment())
        connect(this, SIGNAL(remove_decks()), newDeck, SLOT(close()));
        connect(newDeck, SIGNAL(refresh_decks_signal()), this, SLOT(update_decks()));
        connect(newDeck, SIGNAL(playDeck(QDir)), this, SLOT(play_deck_slott(QDir)));
        scrollbar_layout->addWidget(newDeck, row, column);
        column = column + 1;
        if (column == 2)
        {
            column = 0;
            row = row + 1;
        }
    }
    qDebug() << "All decks added. row:" << row << "column" << column;
    while(row < 2) {
        deck* newDeck = new deck(this);
        newDeck->makeEmptySpace();

        scrollbar_layout->addWidget(newDeck, row, column);
        column = column + 1;
        if (column == 2)
        {
            column = 0;
            row = row + 1;
        }
    }
    qDebug() << "All spacers added. row:" << row << "column" << column;
}

void decks_scroll_bar::play_deck_slott(QDir dir)
{
    qDebug() << "Received dir: " << dir.path();
    emit play_deck_signal(dir);
}
