#ifndef SHOW_CARD_H
#define SHOW_CARD_H

#include <QWidget>

namespace Ui {
class show_card;
}

class show_card : public QWidget
{
    Q_OBJECT

public:
    explicit show_card(QWidget *parent = nullptr);
    ~show_card();

private:
    Ui::show_card *ui;
};

#endif // SHOW_CARD_H
