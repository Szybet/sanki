#ifndef DECKPLAY_H
#define DECKPLAY_H

#include "global.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QTextBrowser>
#include <QMainWindow>
#include <QDir>
#include <QSqlDatabase>

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
    void correctMainCard(QString* mainCard, QFile mediaFile);
    void splitMainCard(QString mainCard, QString* frontCard, QString* backCard);
    void centerText(QTextBrowser* text);
    void resetScrollState();

    bool manageFrontScrollBar = false;
    bool manageBackScrollBar = false;

    void dumpScrollBarInfo(QScrollBar* scroll);
    void scrollBarClone(QScrollBar* scrollbar, QTextBrowser* text);
    void setText(QTextBrowser* area, QString text);
    bool firstLaunch = true;

    sessionStr currectSession;

private slots:
    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::DeckPlay *ui;
    void cardSizeManage(QTextBrowser* text);
};

#endif // DECKPLAY_H
