#include "mainMenu/decks/deck.h"
#include "ui_deck.h"
#include "mainMenu/editGridObject.h"

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
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->deck->setStyleSheet("font-size: 8pt");
    ui->ButtoneditGridObject->setStyleSheet("font-size: 8pt");
    ui->LabelStats->setStyleSheet("font-size: 8pt");
    ui->ButtonDeckSelect->setStyleSheet("font-size: 8pt");

}

void deck::start(QString path) {
    mainPath = path;
    name = path.split(QDir::separator()).last();
    ui->deck->setText(name);
}

void deck::on_ButtoneditGridObject_clicked()
{
    qDebug() << "Edit button clicked, editing deck: " << mainPath;

    editGridObject* edit_widget = new editGridObject();
    edit_widget->deckInfo = mainPath;
    edit_widget->update_deck();

    connect(edit_widget, SIGNAL(refresh_decks_edit_signal()), this, SLOT(refresh_decks_slot()));
    edit_widget->exec();
}

void deck::on_deck_selectionChanged()
{
    // This shows the full name when clicked
    ui->deck->setSelection(0, 0);
    QToolTip::showText( ui->deck->mapToGlobal( QPoint( 0, 0 ) ), mainPath );
}

void deck::on_ButtonDeckSelect_clicked()
{
    emit selectedDeck(mainPath);
}
