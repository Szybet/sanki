#ifndef BOXES_H
#define BOXES_H

#include "cardView/deckPlay.h"
#include "cardView/deckPlay.h"

#include <QObject>

class boxes : public QObject
{
    Q_OBJECT
public:
    explicit boxes(QObject *parent = nullptr);
    bool showedBack = false;
    void loop();
    QString frontCard;
    QString backCard;

public slots:
    void againClicked();
    void hardClicked();
    void goodClicked();
    void easyClicked();

signals:

private:
    DeckPlay* parent;
    Ui::DeckPlay* parentUi;
    QTextBrowser* frontText;
    QTextBrowser* backText;
};

#endif // BOXES_H
