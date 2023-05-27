#ifndef SESSION_H
#define SESSION_H

#include <QWidget>
#include "mainMenu/sessions/sessionStruct.h"

namespace Ui {
class session;
}

class session : public QWidget
{
    Q_OBJECT

public:
    explicit session(QWidget *parent = nullptr);
    ~session();
    void start(QString path);
    sessionStr sessionSaved;
    QTimer* timer;
    bool normalStats = false;

public slots:
    void refreshSessionsSlot();
    void statsManager();

signals:
    void playSession(sessionStr sessionToPlay);
    void refreshSessionsSignal();

private slots:
    void on_ButtonDeckPlay_clicked();
    void on_ButtonOptions_clicked();

    void showRegularStats();
    void showFocusedStats();

    void on_sessionName_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::session *ui;
    bool startBoolIgnoreChanged = true;
    bool changedFocus = true;
};

#endif // SESSION_H
