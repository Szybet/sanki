#ifndef editDeck_H
#define editDeck_H

#include <QDialog>
#include <QDir>
#include <QProxyStyle>
#include <QTimer>

namespace Ui {
class editDeck;
}

class editDeck : public QDialog
{
    Q_OBJECT

public:
    explicit editDeck(QDialog *parent = nullptr);
    ~editDeck();
    QDir deckPath;
    void updateDeck(QDir deckInfo);
    void updateWidget(QString string, int cursor);

signals:
    void refreshDecksSignal();

private slots:
    void on_ButtonRemoveDeck_clicked();
    void on_ButtonCancelEdit_clicked();
    void on_ButtonSaveExit_clicked();
    void on_lineeditDeckName_textChanged(const QString &arg1);


private:
    Ui::editDeck *ui;
    bool updatedName = false;;
    bool removeDeck = false;
    bool firstOpen = true; // this is changed to false after launching in on_lineeditDeckName_cursorPositionChanged
    QTimer* timer;
    void manageKeyboards();
};

#endif // editDeck_H
