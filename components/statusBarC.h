#ifndef statusBarC_H
#define statusBarC_H

#include <QWidget>
#include "components/other/pomodoro.h"

namespace Ui {
class statusBarC;
}

class statusBarC : public QWidget
{
    Q_OBJECT

public:
    explicit statusBarC(QWidget *parent = nullptr);
    ~statusBarC();
    void OptionButtonSet(QString text, QIcon icon, bool enabled);
    void OptionButtonSet2(QString text, QIcon icon, bool enabled);
    void OptionButtonExit(QIcon icon, bool enabled);
    pomodoro* pomodoroWidget;
    void openSettings();

public slots:
    void setStatusText(QString text);
    void receiveDeck(QString call);

private slots:
    void showTime();

    void on_ButtonExit_clicked();

    void on_ButtonOption_clicked();

    void on_ButtonSettings_clicked();

    void on_ButtonOption_2_clicked();

    void on_ButtonStatus_clicked();

signals:
    void optionButtonSignal();
    void closeButtonSignal();
    void option2ButtonSignal();
    void refreshDecksSignal();
    void closedOptionsDialog();
    void tellDeck(QString call);

private:
    Ui::statusBarC *ui;
};

#endif // statusBarC_H
