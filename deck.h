#ifndef DECK_H
#define DECK_H

#include "ui_deck.h"
#include <QDir>

class deck : public QWidget
{
    Q_OBJECT

public:
    deck(QWidget *parent = nullptr);
    QFileInfo deck_info;

public slots:
    void set_deck_name(QString);
    void refresh_decks_slot();

signals:
    void refresh_decks_signal();
    void play_deck(QDir);

private slots:

    void on_EditDeckbutton_clicked();

    void on_ButtonDeckPlay_clicked();

    void on_deck_selectionChanged();

private:
     Ui::MainQwidget *ui;
};

#endif // DECK_H
