#include "deck.h"
#include "ui_deck.h"
#include "edit_deck.h"
#include "mainwindow.h"
#include "deckplay.h"

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
    // https://stackoverflow.com/questions/25855024/aligning-text-in-qtextedit
    ui->deck->setText(text);
    /*
    QTextCursor cursor = ui->deck->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->deck->setTextCursor(cursor);
    */
}

void deck::refresh_decks_slot()
{
    qDebug() << "UPDATE - deck signal";
    emit refresh_decks_signal();
}

void deck::on_EditDeckbutton_clicked()
{
    edit_deck* edit_widget = new edit_deck();
    edit_widget->deck_info = deck_info;
    edit_widget->update_widget();
    edit_widget->show();
    connect(edit_widget, SIGNAL(refresh_decks_edit_signal()), this, SLOT(refresh_decks_slot()));
}


void deck::on_ButtonDeckPlay_clicked()
{

    QDir deck_dir = deck_info.absoluteFilePath();
    qDebug() << "DECKPLAY - DECK";
    emit play_deck(deck_dir);
}

void deck::on_deck_selectionChanged()
{
    // This shows the full name when clicked
    ui->deck->setSelection(0, 0);
    QToolTip::showText( ui->deck->mapToGlobal( QPoint( 0, 0 ) ), deck_info.fileName() );
}

