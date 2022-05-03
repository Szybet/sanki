#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_ButtonLeft_clicked();
    void on_ButtonRight_clicked();
    void request_device_page();
    void on_ScrollBarBrightness_valueChanged(int value);

    void on_ButtonOk_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
