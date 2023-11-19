#ifndef fourOptionsNFlashy_H
#define fourOptionsNFlashy_H

#include <QWidget>

namespace Ui {
class fourOptionsNFlashy;
}

class fourOptionsNFlashy : public QWidget
{
    Q_OBJECT

public:
    explicit fourOptionsNFlashy(QWidget *parent = nullptr);
    ~fourOptionsNFlashy();
    bool enabledButtons = false;

public slots:
    void enableButtons();

signals:
    void again();
    void hard();
    void good();
    void easy();

private slots:
    void on_hardButton_clicked();

    void on_againButton_clicked();

    void on_goodButton_clicked();

    void on_easyButton_clicked();

private:
    Ui::fourOptionsNFlashy *ui;
};

#endif // fourOptionsNFlashy_H
