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

private slots:
    void showTime();

private:
    Ui::status_bar *ui;
};

#endif // STATUS_BAR_H
