#ifndef DECKPLAY_H
#define DECKPLAY_H

#include "global.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QTextBrowser>
#include <QDir>
#include <QSqlDatabase>
#include <QSettings>
#include <QElapsedTimer>

#ifdef EREADER
#include "devicedescriptor.h"
#include "devbattery.h"
#include "devbrightness.h"
#include "einkenums.h"
#include "koboplatformfunctions.h"
#endif

namespace Ui {
class DeckPlay;
}

class DeckPlay : public QWidget
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
    void manageGestures();
    void zoomIn();
    void zoomOut();
    void zoomUpdate();
    bool enabledTapGesture = false;
    bool enabledTapGestureTmp = false; // to ignore tap gestures when they are not needed

    void receiveDeckCall(QString call);
    bool reversedCards = false;

protected:
    bool event(QEvent* event) override;

public slots:
    void showStats();
    // When options dialog is closed
    void reloadSettings();
    void eventSlot(QEvent* eventItem);

signals:
    void saveData();
    void changeStatusBarTextSignal(QString text);
    void tapGesture();

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
    void refreshCard(bool force = false);
    float zoomFactor = 1.0;
    QElapsedTimer* gestureTimer;
    QString previousFrontText;
    QString previousBackText;
};

#endif // DECKPLAY_H
