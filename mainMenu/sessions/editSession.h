#ifndef EDITSESSION_H
#define EDITSESSION_H

#include <QDialog>

#include "mainMenu/sessions/sessionStruct.h"
#include "cardView/modes/boxes/boxes.h"

namespace Ui {
class editSession;
}

class editSession : public QDialog
{
    Q_OBJECT

public:
    explicit editSession(QWidget *parent = nullptr);
    ~editSession();
    void start(sessionStr session);
    sessionStr sessionSaved;
    QSettings* settingsSession;

signals:
    void refreshSessionsSignal();

private slots:
    void on_cancelButton_clicked();

    void on_comboBox_textActivated(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_saveButton_clicked();

    void on_removeSession_toggled(bool checked);

private:
    Ui::editSession *ui;
    bool rename = false;
    bool deleteSession = false;
    bool boxSettingsChanged = false;
    box boxesSettings;

};

#endif // EDITSESSION_H
