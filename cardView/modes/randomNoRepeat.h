#ifndef RANDOMNOREPEAT_H
#define RANDOMNOREPEAT_H

#include "cardView/deckPlay.h"
#include "cardView/buttons/showCard.h"
#include "cardView/deckPlay.h"
#include "ui_deckPlay.h"

#include <QObject>
#include <QSqlDatabase>

class randomNoRepeat: public QObject
{
    Q_OBJECT
public:
    explicit randomNoRepeat(QObject *parent = nullptr);
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

    QVector<QString> firstCards;
    QVector<QString> middleCards;
    QVector<QString> lastCards;
    int maxNumberInList = 0;

    QString lastFirstCardId;
    bool shuffleEverythingNext = false;

    // https://doc.qt.io/qt-5/qtglobal.html#qulonglong-typedef
    QVector<qulonglong> wholeList;

    // At start the whole number of cards is divided by 3 and set to maxNumberInList ( Note: manage odd numbers )
    // then all ID's are put into firstCards ( first order by random ), every showed "card" is put into lastCards
    // if lastCards is full, it is shuffled and moved into middleCards, and middleCards are "inserted" ( without overwriting ) into firstCards
    // And before moving middleCards shuffle it too, just in case
    // If lastFirstCardId is shown second time, completly shuffle everything, propably just run setup once more
    // What this tries to achieve:
    // - Cards don't repeat them selves that fast, until all others are done, but still in not the same order
    // - Randomity
    // - The diffrence from the previous approuch: cards don't fall into "groups" for too long
};

#endif // RANDOMNOREPEAT_H
