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
    void show_back_next();
    void parse_string();

    void mode_crandom_setup();
    void mode_crandom_loop();


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

    QString front_card;
    QString back_card;
    QString main_card;
    bool showed_back = false;


};

#endif // DECKPLAY_H
