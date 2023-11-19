#ifndef SUBSESSION_H
#define SUBSESSION_H

#include <QDialog>

#include "mainMenu/sessions/sessionStruct.h"

namespace Ui {
class subSession;
}

class subSession : public QDialog
{
    Q_OBJECT

public:
    explicit subSession(QWidget *parent = nullptr);
    ~subSession();
    void start(sessionStr sess);
    sessionStr newSession;
    QList<card> cardsSorted;
    int countCards = 0;
    int howManyCards = 0;
    void calculatePercantage();

private slots:
    void on_selectingScrollBar_valueChanged(int value);

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::subSession *ui;
};

#endif // SUBSESSION_H
