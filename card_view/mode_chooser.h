#ifndef MODE_CHOOSER_H
#define MODE_CHOOSER_H

#include <QDialog>

namespace Ui {
class mode_chooser;
}

class mode_chooser : public QDialog
{
    Q_OBJECT

public:
    explicit mode_chooser(QDialog *parent = nullptr);
    ~mode_chooser();

signals:
    void set_mode(int mode);

private slots:
    void on_ButtonCRandom_clicked();
    void on_ButtonConfirm_clicked();

private:
    Ui::mode_chooser *ui;
    int mode = 0;
    // 0 is none
    // 1 is Completly Random
};

#endif // MODE_CHOOSER_H
