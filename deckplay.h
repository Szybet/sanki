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

signals:
    void remove_card();

private:
    Ui::DeckPlay *ui;
    QDir deck_dir;
    int mode;
    QSqlDatabase db;
    QString db_path_str;
};

#endif // DECKPLAY_H
