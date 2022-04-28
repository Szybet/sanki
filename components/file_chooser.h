#ifndef FILE_CHOOSER_H
#define FILE_CHOOSER_H

#include <QDialog>

namespace Ui {
class file_chooser;
}

class file_chooser : public QDialog
{
    Q_OBJECT

public:
    explicit file_chooser(QDialog *parent = nullptr);
    ~file_chooser();

    QString start_path = "/";

public slots:
    void update_files();
    void file_clicked(QString);
    void enter_dir();

signals:
    void remove_buttons();
    void remove_bold();

private slots:
    void on_ButtonConfirm_clicked();

    void on_ButtonUpPath_clicked();

private:
    Ui::file_chooser *ui;
    QString log_file = "file_chooser";
    QString choosed_file;
};

#endif // FILE_CHOOSER_H
