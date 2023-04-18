#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
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
    void get_file(QString file);
    void getMode(DeckModes mode);
    void return_to_mainwindow();

signals:
    void update_decks();
    void clear_mainwidget();
    void close_status_bar();

private slots:
    void FileButton();
    void deck_scroll_bar_show();
    void deckPlay_show(QDir);
    void battery_warning_timer();
    void status_bar_main_menu();

private:
    Ui::MainWindow *ui;
    QString log_file = "MainWindow";
    QString zipFilePath;
    DeckModes mode = None;
};
#endif // MAINWINDOW_H
