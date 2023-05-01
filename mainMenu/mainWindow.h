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

public slots:
    void getFile(QString file); // File chooser uses this
    void getMode(DeckModes mode);
    void returnToStart();
    void addSlotSession();

    void getDeck(QString file);
    void doneSelectingDecks();

    void playSession(sessionStr sessionPlay);

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

private:
    Ui::MainWindow *ui;
    QString zipFilePath;
    DeckModes mode = None;
    fancyGrid* grid;
    statusBarC* statusBarCWidget;
    DeckPlay* playDeck;
    QList<QString> deckPathList;
};
#endif // MAINWINDOW_H
