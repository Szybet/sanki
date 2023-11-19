#ifndef FOUROPTIONS_H
#define FOUROPTIONS_H

#include <QWidget>

namespace Ui {
class fourOptions;
}

class fourOptions : public QWidget
{
    Q_OBJECT

public:
    explicit fourOptions(QWidget *parent = nullptr);
    ~fourOptions();
    void showButtons();
    void hideButtons();

signals:
    void again();
    void hard();
    void good();
    void easy();
    void show();

private slots:
    void on_hardButton_clicked();

    void on_againButton_clicked();

    void on_goodButton_clicked();

    void on_easyButton_clicked();

    void on_showButton_clicked();

private:
    Ui::fourOptions *ui;
};

#endif // FOUROPTIONS_H
