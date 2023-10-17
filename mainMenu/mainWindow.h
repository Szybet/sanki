#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardView/deckPlay.h"
#include "components/statusBarC.h"
#include "global.h"
#include "mainMenu/fancyGrid.h"
#include "mainMenu/sessions/sessionStruct.h"

#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void gestureSignal(QEvent* event);

public slots:
    void getFile(QString file); // File chooser uses this
    void getMode(DeckModes mode);
    void returnToStart();
    void addSlotSession();

    void getDeck(QString file);
    void doneSelectingDecks();
    void updateGrid();

    void playSession(sessionStr sessionPlay);

    void gestureSlot(QEvent* event);
    void exitApp();

private slots:
    void extractDeck();

    void statusBarSessionAdd();
    void statusBarDeckAdd();
    void statusBarPlayAdd();

    void showSessions();
    void showDecks();

    void resetGrid();
    void resetStatusBar();

    void createSession();
    void hardResetDeckPlay();

private:
    Ui::MainWindow *ui;
    QString zipFilePath;
    DeckModes mode = None;
    fancyGrid* grid;
    statusBarC* statusBarCWidget;
    DeckPlay* playDeck;
    QList<QString> deckPathList;
    bool areDecksShown = false;
};
#endif // MAINWINDOW_H
