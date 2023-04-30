#include "mainMenu/fancyGrid.h"
#include "ui_fancyGrid.h"
#include "components/other/griditemspacer.h"

#include <QScrollBar>

fancyGrid::fancyGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fancyGrid)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // This could be editable in settings
    ui->DeckScrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");
}

fancyGrid::~fancyGrid()
{
    delete ui;
}

void fancyGrid::reset() {
    // First kill items, then call this;
    column = 0;
    row = 0;
    widgets.clear();
    emit clearItems();
}

void fancyGrid::addWidget(QWidget* widget) {
    widgets.append(widget);
}

void fancyGrid::show() {
    QGridLayout* layout = ui->DeckGrid;

    foreach(QWidget* widget, widgets) {
        connect(this, &fancyGrid::clearItems, widget, &QWidget::close);
        layout->addWidget(widget, row, column);
        manageCells();
    }

    gridItemSpacer* plus = new gridItemSpacer(this);

    connect(plus, &gridItemSpacer::addItem, this, &fancyGrid::addItem);
    connect(this, &fancyGrid::clearItems, plus, &gridItemSpacer::close);

    plus->selectPage(gridItemSpacer::Page::Add);
    layout->addWidget(plus, row, column);
    manageCells();

    while(row < 2) {
        gridItemSpacer* empty = new gridItemSpacer(this);

        connect(this, &fancyGrid::clearItems, empty, &gridItemSpacer::close);

        empty->selectPage(gridItemSpacer::Page::Empty);
        layout->addWidget(empty, row, column);
        manageCells();
    }
}

void fancyGrid::manageCells() {
    column = column + 1;
    if (column == 2)
    {
        column = 0;
        row = row + 1;
    }
}

void fancyGrid::addItemSlot() {
    emit addItem();
}

/*
void fancyGrid::update_decks()
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
        newDeck->deckInfo = file_info;
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

void fancyGrid::play_deck_slott(QDir dir)
{
    qDebug() << "Received dir: " << dir.path();
    emit play_deck_signal(dir);
}
*/
