#ifndef DECKPLAY_H
#define DECKPLAY_H

#include "global.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QTextBrowser>
#include <QMainWindow>
#include <QDir>
#include <QSqlDatabase>
#include <QSettings>
#include <QElapsedTimer>

namespace Ui {
class DeckPlay;
}

class DeckPlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeckPlay(QWidget *parent = nullptr);
    ~DeckPlay();
    void start(sessionStr newSession);
    void resetScrollState();

    bool manageFrontScrollBar = false;
    bool manageBackScrollBar = false;

    void scrollBarClone(QScrollBar* scrollbar, QTextBrowser* text);
    void setText(QTextBrowser* area, QString text);
    bool firstLaunch = true;

    sessionStr currectSession;
    QList<QSqlDatabase> realSqlDatabases; // Index as in sessionStr::core::deckPathList
    QSettings* saveSession;
    void saveSessionData();
    void exitIt();
    void changeStatusBarTextSlot(QString text); // to be called from modes

public slots:
    void showStats();
    // When options dialog is closed
    void reloadSettings();

signals:
    void saveData();
    void changeStatusBarTextSignal(QString text);

private slots:
    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::DeckPlay *ui;
    void cardSizeManage(QTextBrowser* text);
    QElapsedTimer* elapsedTimer;
    bool already2Minutes = false;
    QTimer* timer;
    bool working = true;
    quint64 timeStartedPlaying;
    int refreshCardRate = 20; // setText is called 2 times every card, so this is 2x then it is in reality to work
    int refreshCardCount = 1;
    void refreshCard();
    void refreshRect(QRect rect);
    void loadWaveFormSetting();
};

#endif // DECKPLAY_H
