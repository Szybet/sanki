#ifndef TOAST_H
#define TOAST_H

#include <QDialog>

namespace Ui {
class toast;
}

class toast : public QDialog
{
    Q_OBJECT

public:
    explicit toast(QDialog *parent = nullptr);
    ~toast();
    QString label_text;
    int show_time_ms = 6000;

public slots:
    void activate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::toast *ui;
};

#endif // TOAST_H
