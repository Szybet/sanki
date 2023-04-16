#include "main_menu/deck.h"
#include "ui_deck.h"
#include "main_menu/edit_deck.h"
#include "main_menu/mainwindow.h"
#include "card_view/deckplay.h"
#include "globals.h"

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QAbstractTextDocumentLayout>
#include <QToolTip>

deck::deck(QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::MainQwidget)
{
    ui->setupUi(this);
    ui->deck->setStyleSheet("font-size: 8pt");
    ui->ButtonEditDeck->setStyleSheet("font-size: 8pt");
    ui->LabelStats->setStyleSheet("font-size: 8pt");
    ui->ButtonDeckPlay->setStyleSheet("font-size: 8pt");

}

void deck::set_deck_name(QString text)
{
    ui->deck->setText(text);
}

void deck::refresh_decks_slot()
{
    qDebug() << "Refresh decks slot received, emitting along";
    emit refresh_decks_signal();
}

void deck::on_ButtonEditDeck_clicked()
{
    qDebug() << "Edit button clicked, editing deck: " << deck_info.baseName();

    edit_deck* edit_widget = new edit_deck();
    edit_widget->deck_info = deck_info;
    edit_widget->update_deck();

    connect(edit_widget, SIGNAL(refresh_decks_edit_signal()), this, SLOT(refresh_decks_slot()));
    edit_widget->exec();
}


void deck::on_ButtonDeckPlay_clicked()
{
    QDir deckDir = deck_info.absoluteFilePath();
    qDebug() << "Clicked at dir: " << deckDir.path();
    emit playDeck(deckDir);
}

void deck::on_deck_selectionChanged()
{
    // This shows the full name when clicked
    ui->deck->setSelection(0, 0);
    QToolTip::showText( ui->deck->mapToGlobal( QPoint( 0, 0 ) ), deck_info.fileName() );
}

// Hides everything, only used to make the grid the right size
void deck::makeEmptySpace() {
    ui->ButtonDeckPlay->hide();
    ui->ButtonEditDeck->hide();
    ui->deck->hide();
    ui->LabelStats->hide();
    ui->line->hide();
}
