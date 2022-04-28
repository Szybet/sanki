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

signals:
    void update_decks();
    void clear_mainwidget();

private slots:
    void on_CloseButton_clicked();
    void on_FileButton_clicked();
    void exit_app();
    void deck_scroll_bar_show();
    void deck_play_show(QDir);

private:
    Ui::MainWindow *ui;
    QString log_file = "MainWindow";
    QString zip_file_path;

};
#endif // MAINWINDOW_H
