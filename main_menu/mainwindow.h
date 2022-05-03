#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void get_mode(int mode);

signals:
    void update_decks();
    void clear_mainwidget();

private slots:
    void FileButton();
    void deck_scroll_bar_show();
    void deck_play_show(QDir);
    void battery_warning_timer();

private:
    Ui::MainWindow *ui;
    QString log_file = "MainWindow";
    QString zip_file_path;
    int mode = 0;

};
#endif // MAINWINDOW_H
