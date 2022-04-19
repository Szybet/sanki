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
    void next_card();
    void show_back_next();

signals:
    void show_button_text(QString);

private:
    Ui::DeckPlay *ui;
    QDir deck_dir;
    int mode;
    QSqlDatabase db;
    QString db_path_str;
    QString front_card;
    QString back_card;
    bool showed_back = false;


};

#endif // DECKPLAY_H
