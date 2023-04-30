#ifndef DECKPLAY_H
#define DECKPLAY_H

#include "global.h"
#include "qtextbrowser.h"
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
    void update(QDir, DeckModes modeNew);
    void correctString(QString* mainCard);
    void splitMainCard(QString mainCard, QString* frontCard, QString* backCard);
    void centerText(QTextBrowser* text);
    void resetScrollState();

    bool manageFrontScrollBar = false;
    bool manageBackScrollBar = false;

    void dumpScrollBarInfo(QScrollBar* scroll);
    void scrollBarClone(QScrollBar* scrollbar, QTextBrowser* text);
    void setText(QTextBrowser* area, QString text);
    bool firstLaunch = true;

private slots:
    void start();

    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::DeckPlay *ui;
    QDir deckDir;
    DeckModes mode;
    QFile mediaFile;
    QSqlDatabase db;
    void cardSizeManage(QTextBrowser* text);
};

#endif // DECKPLAY_H
