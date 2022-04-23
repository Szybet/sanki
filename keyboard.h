#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QDialog>

namespace Ui {
class keyboard;
}

class keyboard : public QDialog
{
    Q_OBJECT

public:
    explicit keyboard(QDialog *parent = nullptr);
    ~keyboard();
    QString main_string;
    QString edited_string;
    int cursor_main;

signals:
    void update_data(QString string, int cursor);

private slots:
    void update_string(QString new_string);
    void on_Button_q_clicked();

private:
    Ui::keyboard *ui;
    bool init = false;
};

#endif // KEYBOARD_H
