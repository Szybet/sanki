#ifndef DECKS_SCROLL_BAR_H
#define DECKS_SCROLL_BAR_H

#include <QWidget>
#include <QDir>

namespace Ui {
class decks_scroll_bar;
}

class decks_scroll_bar : public QWidget
{
    Q_OBJECT

public:
    explicit decks_scroll_bar(QWidget *parent = nullptr);
    ~decks_scroll_bar();

public slots:
    void update_decks();
    void play_deck_slott();

signals:
    void remove_decks();
    void play_deck_signal();

private:
    Ui::decks_scroll_bar *ui;

};

#endif // DECKS_SCROLL_BAR_H
