#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QWidget>
#include "components/other/pomodoro.h"
#include "components/statusBarC.h"

namespace Ui {
class settingsMenu;
}

class settingsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit settingsMenu(QWidget *parent = nullptr);
    ~settingsMenu();
    void start(pomodoro* pomodoroWidgetParent, statusBarC* statusBarParent);
    void exitWidgetCheck();

private slots:
    void on_settingsButton_clicked();

    void on_pomodoroButton_clicked();

private:
    Ui::settingsMenu *ui;
    pomodoro* pomodoroWidget;
    statusBarC* statusBar;
};

#endif // SETTINGSMENU_H
