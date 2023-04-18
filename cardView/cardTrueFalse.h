#ifndef CARD_TRUE_FALSE_H
#define CARD_TRUE_FALSE_H

#include <QWidget>

namespace Ui {
class cardTrueFalse;
}

class cardTrueFalse : public QWidget
{
    Q_OBJECT

public:
    explicit cardTrueFalse(QWidget *parent = nullptr);
    ~cardTrueFalse();

private:
    Ui::cardTrueFalse *ui;
};

#endif // CARD_TRUE_FALSE_H
