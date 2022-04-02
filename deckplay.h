#ifndef DECKPLAY_H
#define DECKPLAY_H

#include <QMainWindow>
#include <QDir>
#include <QSqlDatabase>

namespace Ui {
class DeckPlay;
}

class DeckPlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeckPlay(QWidget *parent = nullptr);
    ~DeckPlay();

public slots:
    void update(QDir, int);

private slots:
    void start();

private:
    Ui::DeckPlay *ui;
    QDir deck_dir;
    int mode;
    QSqlDatabase db;
};

#endif // DECKPLAY_H
