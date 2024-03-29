#ifndef BOXES_H
#define BOXES_H

#include "cardView/deckPlay.h"
#include "cardView/buttons/fourOptions.h"

#include <ui_deckPlay.h>
#include <QObject>
#include <QTextBrowser>

/*

QList<QList<uint>> is the main idea ( with index from card list )
all go to the 0 list, and then if the card is showed, buttons do:

variable to set for each button how much should it go, if it can't go as much back it will be last on the first list

- again: default -2
- hard: default -1
- good: default 1
- easy: default 2

all those setting saved in a section of the qsettings named box
*/

struct cardIndex {
    uint index = 0;
    uint skip = 0; // Skip is set when moving a card, to avoid showing it in a loop. It's only added if needed, like there are less cards in front of it then the skip value
};
Q_DECLARE_METATYPE(cardIndex)

struct box {
    uint howMuchBoxes = 4;
    QList<QList<cardIndex>> boxes;
    int againValue = -2;
    int hardValue = -1;
    int goodValue = 1;
    int easyValue = 2;
    uint defaultSkipValue = 10;
    uint startingBox = 2; // middle -1 should be good - this starts from 0 but is 1 in the gui
};
Q_DECLARE_METATYPE(box)

class boxes : public QObject
{
    Q_OBJECT
public:
    explicit boxes(QObject *parent = nullptr);
    void loop();
    void setup(DeckPlay* parentArg, Ui::DeckPlay* parentUiArg);
    QString frontCard;
    QString backCard;
    box theBox;
    uint currentCardIndex;
    void moveCard(int moveValue);
    QList<int> boxesCardCount;
    void cardStatUpdate(int inWhichBox, int moveCard); // Launch from boxes mode when new card is selected, otherwise hide the widget. moveCard 0 does nothing

public slots:
    void againClicked();
    void hardClicked();
    void goodClicked();
    void easyClicked();
    void showBack();

    void saveBox();

signals:

private:
    DeckPlay* parent;
    Ui::DeckPlay* parentUi;
    QTextBrowser* frontText;
    QTextBrowser* backText;
    bool readyToSave = false;

    // Tmp values pointing to current card, indexes
    int whichBox; // int because there is a - operation
    int whichCard;
};

extern QDebug operator<<(QDebug dbg, const cardIndex& c);
extern QDataStream& operator<<(QDataStream& out, const cardIndex& v);
extern QDataStream& operator>>(QDataStream& in, cardIndex& v);

extern QDebug operator<<(QDebug dbg, const box& c);
extern QDataStream& operator<<(QDataStream& out, const box& v);
extern QDataStream& operator>>(QDataStream& in, box& v);

#endif // BOXES_H
