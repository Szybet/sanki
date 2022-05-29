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
    void check_if_scrollbars_showe();

private slots:
    void start();
    void show_back_next();
    void parse_string();

    void mode_crandom_setup();
    void mode_crandom_loop();

    void mode_random_norepeat_setup();
    void mode_random_norepeat_loop();

    void on_textBackCard_textChanged();
    void on_textFrontCard_textChanged();
    void on_horizontalScrollBar_valueChanged(int value);

signals:
    void show_button_text(QString);

    void next_card_call();

private:
    Ui::DeckPlay *ui;
    QString log_file = "deckplay";
    QDir deck_dir;
    int mode;
    QFile media_file;

    QSqlDatabase db;
    QString db_path_str;

    bool first_launch = true;
    QString front_card;
    QString back_card;
    QString main_card;
    bool showed_back = false;

    int scroll_bar_setted_front = 0;
    int scroll_bar_setted_back = 0;
    bool hor_scroll_front_needed = false;
    bool hor_scroll_back_needed = false;

    int no_repeat_list;
    QStringList no_repeat_ids;
};

#endif // DECKPLAY_H
