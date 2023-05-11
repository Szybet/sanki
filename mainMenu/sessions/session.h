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

private:
    Ui::session *ui;
};

#endif // SESSION_H
