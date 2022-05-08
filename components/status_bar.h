#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <QWidget>

namespace Ui {
class status_bar;
}

class status_bar : public QWidget
{
    Q_OBJECT

public:
    explicit status_bar(QWidget *parent = nullptr);
    ~status_bar();
    void option_button_set(QString, QIcon);
    void option_button_enabled(bool);

private slots:
    void showTime();

    void on_ButtonExit_clicked();

    void on_ButtonOption_clicked();

    void on_ButtonSettings_clicked();

signals:
    void option_button_signal();
    void close_button_signal();

private:
    Ui::status_bar *ui;
};

#endif // STATUS_BAR_H
