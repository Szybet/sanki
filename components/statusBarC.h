#ifndef statusBarC_H
#define statusBarC_H

#include <QWidget>

namespace Ui {
class statusBarC;
}

class statusBarC : public QWidget
{
    Q_OBJECT

public:
    explicit statusBarC(QWidget *parent = nullptr);
    ~statusBarC();
    void OptionButtonSet(QString text, QIcon icon, bool enabled);
    void OptionButtonSet2(QString text, QIcon icon, bool enabled);
    void OptionButtonExit(QIcon icon, bool enabled);

private slots:
    void showTime();

    void on_ButtonExit_clicked();

    void on_ButtonOption_clicked();

    void on_ButtonSettings_clicked();

    void on_ButtonOption_2_clicked();

signals:
    void optionButtonSignal();
    void closeButtonSignal();
    void option2ButtonSignal();
    void refreshDecksSignal();

private:
    Ui::statusBarC *ui;
};

#endif // statusBarC_H
