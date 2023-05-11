#include "mainMenu/fancyGrid.h"
#include "qdebug.h"
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
    qDebug() << "Reset grid called";

    emit clearItems();
    QApplication::processEvents();
    widgets.clear();

    ui->DeckGrid->invalidate();

    column = 0;
    row = 0;

    this->disconnect();
}

void fancyGrid::addWidget(QWidget* widget) {
    widgets.append(widget);
}

void fancyGrid::showWidgets() {
    QGridLayout* layout = ui->DeckGrid;

    foreach(QWidget* widget, widgets) {
        connect(this, &fancyGrid::clearItems, widget, &QWidget::close);
        qDebug() << "current row:" << row << "column:" << column;
        layout->addWidget(widget, row, column, 1, 1);
        manageCells();
    }

    // Don't show if it's needed to create a seperate row
    if(widgets.isEmpty() == true || column == 1 || row == 1) {
        gridItemSpacer* plus = new gridItemSpacer(this);
        connect(plus, &gridItemSpacer::addItem, this, &fancyGrid::addItem);
        connect(this, &fancyGrid::clearItems, plus, &QWidget::close);
        plus->selectPage(gridItemSpacer::Page::Add);
        // So for no reason at all if 2 diffrent widgets are in a grid layout, sizes go duck themselves and it lookg awfull. This makes this widget minimum size, so it doesn't try to move decks
        layout->addWidget(plus, row, column, 1, 1, Qt::AlignJustify);
        qDebug() << "current row:" << row << "column:" << column;
        manageCells();
    }

    while(row < 2) {
        gridItemSpacer* empty = new gridItemSpacer(this);
        connect(this, &fancyGrid::clearItems, empty, &QWidget::close);

        empty->selectPage(gridItemSpacer::Page::Empty);
        layout->addWidget(empty, row, column, 1, 1, Qt::AlignJustify);
        qDebug() << "current row:" << row << "column:" << column;
        manageCells();
    }

    qDebug() << layout->columnCount() << layout->rowCount();
}

void fancyGrid::manageCells() {
    column = column + 1;
    if (column == 2)
    {
        column = 0;
        row = row + 1;
    } else if(column > 2) {
        qCritical() << "Column is above limit";
    }
}

void fancyGrid::addItemSlot() {
    emit addItem();
}

/*
void fancyGrid::updateDecks()
{
    qDebug() << "updateDecks slot called";
    emit removeDecks();

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
        connect(this, SIGNAL(removeDecks()), newDeck, SLOT(close()));
        connect(newDeck, SIGNAL(refresh_decks_signal()), this, SLOT(updateDecks()));
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
