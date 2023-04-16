#ifndef EDIT_DECK_H
#define EDIT_DECK_H

#include <QDialog>
#include <QDir>
#include <QProxyStyle>

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
    void on_lineEditDeckName_cursorPositionChanged(int arg1, int arg2);
    void keyboard_closed(bool update_name);
    void on_lineEditDeckName_selectionChanged();

private:
    Ui::edit_deck *ui;
    bool updated_name;
    bool reset_deck = false;
    bool remove_deck = false;
    QString log_file = "edit_deck.cpp";
    QVector<QString> log_message;
    QVector<QString> log_function;
    bool first_open = true; // this is changed to false after launching in on_lineEditDeckName_cursorPositionChanged
    bool keyboard_opened = false;
};

#endif // EDIT_DECK_H
