#ifndef EDIT_DECK_H
#define EDIT_DECK_H

#include <QWidget>
#include <QDir>

namespace Ui {
class edit_deck;
}

class edit_deck : public QWidget
{
    Q_OBJECT

public:
    explicit edit_deck(QWidget *parent = nullptr);
    ~edit_deck();
    QFileInfo deck_info;

public slots:
    void update_widget();

signals:
    void refresh_decks_edit_signal();

private slots:
    void on_ButtonRemoveDeck_clicked();

    void on_textEditDeckName_textChanged();

    void on_ButtonReset_clicked();

    void on_ButtonCancelEdit_clicked();

    void on_ButtonSaveExit_clicked();

private:
    Ui::edit_deck *ui;
    QString updated_name;
    bool reset_deck = false;
    bool remove_deck = false;
};

#endif // EDIT_DECK_H
