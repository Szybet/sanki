#ifndef POMODORO_H
#define POMODORO_H

#include <QDialog>
#include "QTimer"
#include "QSettings"

namespace Ui {
class pomodoro;
}

class pomodoro : public QDialog
{
    Q_OBJECT

public:
    explicit pomodoro(QWidget *parent = nullptr);
    ~pomodoro();
    int timeLeft = -5; // Time left for anything that is going now, in s / -5 for starting it
    QString timeLeftFun();
    enum pomodoroStatus {
        pomodoroLearning,
        breakNormal,
        breakLong,
    };
    pomodoroStatus status = pomodoroLearning;
    int pomodoroDur = 25;
    int breakNormalDur = 5;
    int breakLongDur = 15;
    int countPomodorosUntilLong = 4;
    void mainFunction();
    int counterBreaks = 0;
    int timeLeftMax = 25;
    void updateBreakLabel();

private slots:
    void on_enableBox_stateChanged(int arg1);

    void on_pomodoroDurationBox_valueChanged(int arg1);

    void on_breakDurationBox_valueChanged(int arg1);

    void on_longBreakDurationBox_valueChanged(int arg1);

    void on_xBeforeBreakBox_valueChanged(int arg1);

private:
    Ui::pomodoro *ui;
    QTimer* timer;
    QSettings* settingsGlobal;
};

#endif // POMODORO_H
