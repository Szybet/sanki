#ifndef fileChooserCustom_H
#define fileChooserCustom_H

#include <QDialog>
#include <QFileInfo>

namespace Ui {
class fileChooserCustom;
}

class fileChooserCustom : public QDialog
{
    Q_OBJECT

public:
    explicit fileChooserCustom(QDialog *parent = nullptr);
    ~fileChooserCustom();

    QString start_path = "/";
    QFileInfo deckInfo;
    QString file_extension = ".apkg";

public slots:
    void updateFiles();
    void file_clicked(QString);
    void enter_dir();

    // Keyboard:
    void updateWidget(QString string, int cursor);
    void updateDeck();

signals:
    void remove_buttons();
    void remove_bold();
    void provideFile(QString file);

private slots:
    void on_ButtonConfirm_clicked();

    void on_ButtonCancel_clicked();

    void on_ButtonUpPath_clicked();

    // Keyboard:
    void on_lineEditPath_selectionChanged();
    void keyboardClosed(bool updateName);
    void on_lineEditPath_cursorPositionChanged(int arg1, int arg2);



private:
    Ui::fileChooserCustom *ui;
    QString log_file = "fileChooserCustom";
    QString choosed_file;

    // Keyboard:
    bool updatedName;
    bool firstOpen = true; // this is changed to false after launching in on_lineeditDeckName_cursorPositionChanged
    bool keyboardOpened = false;
};

#endif // fileChooserCustom_H
