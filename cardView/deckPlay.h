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

private slots:
    void start();

    void modeRandomNoRepeatSetup();
    void modeRandomNoRepeatLoop();

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
};

#endif // DECKPLAY_H
