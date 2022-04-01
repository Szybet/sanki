#ifndef DECKPLAY_H
#define DECKPLAY_H

#include <QMainWindow>
#include <QDir>

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
    void provide_deck(QDir);
    void start();

private:
    Ui::DeckPlay *ui;
    QDir deck_dir;
};

#endif // DECKPLAY_H
