#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

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
    void on_ScrollBarBrightness_valueChanged(int value);
    void on_ButtonOk_clicked();
    void requestEreaderPage();
    void requestMenuPage();
    void requestSyncPage();
    void on_buttonSyncInfo_clicked();
    void on_buttonSync_clicked();
    void on_checkBox_stateChanged(int arg1);

    void on_ButtonFontChange_clicked();

    void on_buttonEinkInfo_clicked();

    void on_comboBoxEinkMode_currentTextChanged(const QString &arg1);

    void on_buttonDebuggingData_clicked();

private:
    Ui::Settings *ui;
    enum Direction{
        Right,
        Left,
    };
    void managePage(int newIndex, Direction fromWhere);
    bool overwriteDeck = false;
    QTimer* timer;
    void manageKeyboards();
    QSettings* settingsGlobal;
    QFont currentFont;
    QString waveFormNumbToString(int numb);
    int waveFormStringToInt(QString name);
};

#endif // SETTINGS_H
