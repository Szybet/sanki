#ifndef SHOW_CARD_H
#define SHOW_CARD_H

#include <QWidget>

namespace Ui {
class showCard;
}

class showCard : public QWidget
{
    Q_OBJECT

public:
    explicit showCard(QWidget *parent = nullptr);
    ~showCard();

public slots:
    void setText(QString);

signals:
    void clicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::showCard *ui;
};

#endif // SHOW_CARD_H
