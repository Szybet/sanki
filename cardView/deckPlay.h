#ifndef DECKPLAY_H
#define DECKPLAY_H

#include "globals.h"
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

private slots:
    void start();

    void modeRandomNoRepeatSetup();
    void modeRandomNoRepeatLoop();

    void on_textFrontCard_textChanged();

    void on_textBackCard_textChanged();

    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::DeckPlay *ui;
    QString log_file = "deckplay";
    QDir deckDir;
    DeckModes mode;
    QFile mediaFile;

    QSqlDatabase db;

    bool firstLaunch = true;

    int no_repeat_list;
    QStringList no_repeat_ids;

    void cardSizeManage(QTextBrowser* text);
};

#endif // DECKPLAY_H
