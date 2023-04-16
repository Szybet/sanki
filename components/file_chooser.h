#ifndef FILE_CHOOSER_H
#define FILE_CHOOSER_H

#include <QDialog>
#include <QFileInfo>

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
    QFileInfo deck_info;
    QString file_extension = ".apkg";

public slots:
    void update_files();
    void file_clicked(QString);
    void enter_dir();

    // Keyboard:
    void update_widget(QString string, int cursor);
    void update_deck();

signals:
    void remove_buttons();
    void remove_bold();
    void provide_file(QString file);

private slots:
    void on_ButtonConfirm_clicked();

    void on_ButtonCancel_clicked();

    void on_ButtonUpPath_clicked();

    // Keyboard:
    void on_lineEditPath_selectionChanged();
    void keyboard_closed(bool update_name);
    void on_lineEditPath_cursorPositionChanged(int arg1, int arg2);



private:
    Ui::file_chooser *ui;
    QString log_file = "file_chooser";
    QString choosed_file;

    // Keyboard:
    bool updatedName;
    bool first_open = true; // this is changed to false after launching in on_lineEditDeckName_cursorPositionChanged
    bool keyboard_opened = false;
};

#endif // FILE_CHOOSER_H
