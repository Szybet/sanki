#ifndef editGridObject_H
#define editGridObject_H

#include <QDialog>
#include <QDir>
#include <QProxyStyle>

namespace Ui {
class editGridObject;
}

class editGridObject : public QDialog
{
    Q_OBJECT

public:
    explicit editGridObject(QDialog *parent = nullptr);
    ~editGridObject();
    QFileInfo deckInfo;

public slots:
    void update_widget(QString string, int cursor);
    void update_deck();

signals:
    void refresh_decks_edit_signal();
    void provide_text(QString string, int cursor);

private slots:
    void on_ButtonRemoveDeck_clicked();
    void on_ButtonReset_clicked();
    void on_ButtonCancelEdit_clicked();
    void on_ButtonSaveExit_clicked();
    void on_lineeditGridObjectName_cursorPositionChanged(int arg1, int arg2);
    void keyboard_closed(bool update_name);
    void on_lineeditGridObjectName_selectionChanged();

    void on_lineeditGridObjectName_textChanged(const QString &arg1);

private:
    Ui::editGridObject *ui;
    bool updatedName = false;;
    bool reset_deck = false;
    bool remove_deck = false;
    bool first_open = true; // this is changed to false after launching in on_lineeditGridObjectName_cursorPositionChanged
    bool keyboard_opened = false;
};

#endif // editGridObject_H
