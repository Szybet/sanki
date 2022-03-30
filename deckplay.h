#ifndef DECKPLAY_H
#define DECKPLAY_H

#include <QMainWindow>

namespace Ui {
class DeckPlay;
}

class DeckPlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeckPlay(QWidget *parent = nullptr);
    ~DeckPlay();

private:
    Ui::DeckPlay *ui;
};

#endif // DECKPLAY_H
