#ifndef COMPLETLYRANDOM_H
#define COMPLETLYRANDOM_H

#include "cardView/deckPlay.h"
#include "cardView/showCard.h"
#include "cardView/deckPlay.h"
#include "ui_deckPlay.h"
#include <QObject>
#include <QSqlDatabase>

class CompletlyRandom: public QObject
{
    Q_OBJECT
public:
    explicit CompletlyRandom(QObject *parent = nullptr);
    bool showedBack = false;
    void loop();
    QString frontCard;
    QString backCard;
    QString mainCard;

signals:
    void setText(QString text);

public slots:
    void setup(DeckPlay* parentArg, Ui::DeckPlay* parentUiArg, QSqlDatabase* dbArg);
    void buttonClicked();

private:
    showCard* buttonWidget;
    DeckPlay* parent;
    Ui::DeckPlay* parentUi;
    QSqlDatabase* db;
    QTextBrowser* frontText;
    QTextBrowser* backText;
};

#endif // COMPLETLYRANDOM_H
