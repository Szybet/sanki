#ifndef DECK_H
#define DECK_H

#include "ui_deck.h"

class deck : public QWidget
{
    Q_OBJECT

public:
    deck(QWidget *parent = nullptr);

public slots:
    void set_deck_name(QString);

private slots:

private:
     Ui::MainQwidget *ui;
};

#endif // DECK_H
