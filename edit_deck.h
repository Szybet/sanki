#ifndef EDIT_DECK_H
#define EDIT_DECK_H

#include <QDialog>
#include <QDir>

namespace Ui {
class edit_deck;
}

class edit_deck : public QDialog
{
    Q_OBJECT

public:
    explicit edit_deck(QDialog *parent = nullptr);
    ~edit_deck();
    QFileInfo deck_info;

    // https://stackoverflow.com/questions/24642370/qmetaobjectinvokemethod-no-such-method-when-using-inheritance
    // + no variables
    Q_INVOKABLE void log();

public slots:
    void update_widget(QString string, int cursor);


signals:
    void refresh_decks_edit_signal();
    void provide_text(QString string, int cursor);

private slots:
    void on_ButtonRemoveDeck_clicked();

    void on_ButtonReset_clicked();

    void on_ButtonCancelEdit_clicked();

    void on_ButtonSaveExit_clicked();

    void on_lineEditDeckName_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::edit_deck *ui;
    QString updated_name;
    bool reset_deck = false;
    bool remove_deck = false;
    QString log_file = "edit_deck.cpp";
    QVector<QString> log_message;
    QVector<QString> log_function;
    bool first_open = true; // this is changed to false after launching in on_lineEditDeckName_cursorPositionChanged
};

#endif // EDIT_DECK_H
