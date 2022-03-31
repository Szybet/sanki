#ifndef CARD_TRUE_FALSE_H
#define CARD_TRUE_FALSE_H

#include <QWidget>

namespace Ui {
class card_true_false;
}

class card_true_false : public QWidget
{
    Q_OBJECT

public:
    explicit card_true_false(QWidget *parent = nullptr);
    ~card_true_false();

private:
    Ui::card_true_false *ui;
};

#endif // CARD_TRUE_FALSE_H
