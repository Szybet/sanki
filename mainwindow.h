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

private slots:
    void on_CloseButton_clicked();
    void showTime();
    void on_FileButton_clicked();
    void update_decks(QDir);

signals:
    void remove_decks();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
