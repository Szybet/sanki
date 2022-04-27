#ifndef FILE_H
#define FILE_H

#include <QWidget>

namespace Ui {
class file;
}

class file : public QWidget
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = nullptr);
    ~file();
    bool is_directory = false;
    void set_button_look(QString, QIcon);

signals:
    void im_clicked(QString);

public slots:
    void remove_bold();

private slots:
    void on_pushButton_clicked();

private:
    Ui::file *ui;
    bool ignore_remove_bold_signal = false;
};

#endif // FILE_H
