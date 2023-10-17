#include "boxes.h"
#include "cardView/deckPlay.h"
#include "ui_deckPlay.h"
#include "cardView/functions/helperFunctions.h"
#include "cardView/modes/boxes/askforboxesoptions.h"
#include "cardView/buttons/fourOptionsNFlashy.h"

#include <QObject>
#include <QDebug>
#include <QTimer>

#define SMALL_STATS_UPDATE_DELAY 2000

boxes::boxes(QObject *parent)
    : QObject{parent}
{

}

void boxes::setup(DeckPlay* parentArg, Ui::DeckPlay* parentUiArg) {
    parent = parentArg;
    parentUi = parentUiArg;
    frontText = parentUi->textFrontCard;
    backText = parentUi->textBackCard;

    if(parent->enabledTapGesture == false) {
        fourOptions* buttons = new fourOptions();
        connect(buttons, &fourOptions::again, this, &boxes::againClicked);
        connect(buttons, &fourOptions::hard, this, &boxes::hardClicked);
        connect(buttons, &fourOptions::good, this, &boxes::goodClicked);
        connect(buttons, &fourOptions::easy, this, &boxes::easyClicked);
        connect(buttons, &fourOptions::show, this, &boxes::showBack);
        parentUi->gridManageCard->addWidget(buttons);
    } else {
        fourOptionsNFlashy* buttons = new fourOptionsNFlashy();
        connect(buttons, &fourOptionsNFlashy::again, this, &boxes::againClicked);
        connect(buttons, &fourOptionsNFlashy::hard, this, &boxes::hardClicked);
        connect(buttons, &fourOptionsNFlashy::good, this, &boxes::goodClicked);
        connect(buttons, &fourOptionsNFlashy::easy, this, &boxes::easyClicked);
        connect(parent, &DeckPlay::tapGesture, this, &boxes::showBack);
        connect(parent, &DeckPlay::tapGesture, buttons, &fourOptionsNFlashy::enableButtons); // enable buttons with tap
        parentUi->gridManageCard->addWidget(buttons);
    }

    if(parent->saveSession->value("boxMode/box").isNull() == true && parent->saveSession->value("boxMode/box").isValid() == false) {
        qDebug() << "There is no saved config for box mode, asking things";
        theBox = box();
        askForBoxesOptions* options = new askForBoxesOptions(parent);
        options->start(&theBox);
        options->exec();

        for(uint i = 0; i < theBox.howMuchBoxes; i++) {
            theBox.boxes.append(QList<cardIndex>());
        }

        qDebug() << "parent->currectSession.cardList.count():" << parent->currectSession.cardList.count();

        for(int i = 0; i < parent->currectSession.cardList.count(); i++) {
            cardIndex newIndex = cardIndex();
            newIndex.index = i;

            // Start box value
            theBox.boxes[theBox.startingBox - 1].append(newIndex);
        }

        qDebug() << "New settings from box:" << theBox;

        readyToSave = true;
        saveBox();
    } else {
        qDebug() << "There is already saved config";
        theBox = parent->saveSession->value("boxMode/box").value<box>();
        qDebug() << "The box:" << theBox;

    }
    readyToSave = true;

    cardStatUpdate(theBox.startingBox - 1, 0);
    loop();
}

void boxes::loop() {
    // Disable the line for better eink
    parentUi->lineMiddleText->setVisible(false);

    // Looking for the next card
    // i - box
    // ii - card
    bool first = true;
    uint whichBoxFirst;
    uint whichCardFirst;

    bool found = false;
    for(uint i = 0; i < theBox.howMuchBoxes; i++) {
        if(found == true) {
            break;
        }
        for(int ii = 0; ii < theBox.boxes[i].count(); ii++) {
            if(first == true) {
                first = false;
                whichBoxFirst = i;
                whichCardFirst = ii;
            }

            if(theBox.boxes[i][ii].skip == 0) {
                qDebug() << "Found card:" << theBox.boxes[i][ii];
                whichBox = i;
                whichCard = ii;
                found = true;
                break;
            } else {
                theBox.boxes[i][ii].skip -= 1;
            }
        }
    }
    if(first == true) {
        qWarning() << "Didn't found any card to view? The program will propably crash";
    }
    // All cards have a skip attribute - so choosing the first one in the row
    if(found == false && first == false) {
        whichBox = whichBoxFirst;
        whichCard = whichCardFirst;
    }

    card* choosenCard = &parent->currectSession.cardList[theBox.boxes[whichBox][whichCard].index];

    QString deckName = parent->currectSession.core.deckPathList[choosenCard->deckiD];
    deckName = deckName.split("/").last();
    qDebug() << "Deck name for card:" << deckName;
    if(deckName.length() > 20) {
        deckName = deckName.left(20);
        deckName.append("...");
    }
    parent->changeStatusBarTextSlot(deckName);

    qDebug() << "Choosed card:" << choosenCard;
    choosenCard->count += 1;

    QString mainCard = cardExtract(choosenCard, parent);

    correctMainCard(&mainCard, findMediaFile(choosenCard, &parent->currectSession));
    splitMainCard(mainCard, &frontCard, &backCard);

    QString searchPath = directories::deckStorage.filePath(parent->currectSession.core.deckPathList[choosenCard->deckiD]);
    frontText->setSearchPaths(QStringList(searchPath));
    backText->setSearchPaths(QStringList(searchPath));

    parent->resetScrollState();

    backText->hide();
    parent->setText(frontText, frontCard);

    // Before changing anything
    int whichBoxTmp = whichBox;
    QTimer::singleShot(SMALL_STATS_UPDATE_DELAY, this, [this, whichBoxTmp]() {
        cardStatUpdate(whichBoxTmp, 0);
    });
}

void boxes::againClicked() {
    qDebug() << "Clicked again button";
    moveCard(theBox.againValue);
}
void boxes::hardClicked() {
    qDebug() << "Clicked hard button";
    moveCard(theBox.hardValue);
}
void boxes::goodClicked() {
    qDebug() << "Clicked good button";
    moveCard(theBox.goodValue);
}
void boxes::easyClicked() {
    qDebug() << "Clicked easy button";
    moveCard(theBox.easyValue);
}

void boxes::showBack() {
    qDebug() << "Clicked show button";
    // simple checker ;)
    if(parentUi->lineMiddleText->isVisible() == false) {
        parentUi->lineMiddleText->setVisible(true);
        backText->show();
        parent->setText(backText, backCard);
    }
}

void boxes::moveCard(int moveValue) {
    cardIndex savedCardIndex = theBox.boxes[whichBox][whichCard];
    // Removing the card from current position
    theBox.boxes[whichBox].removeAt(whichCard);

    // Before changing anything
    int whichBoxTmp = whichBox;
    QTimer::singleShot(SMALL_STATS_UPDATE_DELAY, this, [this, whichBoxTmp, moveValue]() {
        cardStatUpdate(whichBoxTmp, moveValue);
    });


    // Choosing the new box
    whichBox = whichBox + moveValue;
    if(whichBox < 0) {
        qDebug() << "The box choosed is less than 0";
        whichBox = 0;
    } else if((uint)whichBox > theBox.howMuchBoxes - 1) {
        qDebug() << "The box is more than allowed";
        whichBox = theBox.howMuchBoxes - 1;
    }

    int newSkipValue = theBox.defaultSkipValue - theBox.boxes[whichBox].count();

    if(newSkipValue < 0) {
        newSkipValue = 0;
    }
    qDebug() << "newSkipValue:" << newSkipValue;

    savedCardIndex.skip = newSkipValue;

    theBox.boxes[whichBox].append(savedCardIndex);

    loop();
}

void boxes::saveBox() {
    if(readyToSave == true) {
        qDebug() << "Saving data in boxes";
        QVariant variant = QVariant::fromValue(theBox);
        parent->saveSession->setValue("boxMode/box", variant);
    }
}

void boxes::cardStatUpdate(int inWhichBox, int moveCard) {
    // Fill it up
    if(boxesCardCount.isEmpty()) {
        qDebug() << "Filling up boxesCardCount:" << theBox.boxes.count();
        for(int i = 0; i < theBox.boxes.count(); i++) {
            boxesCardCount.append(theBox.boxes[i].count());
        }
    }

    int newBox = inWhichBox + moveCard;

    // Coppied from move Card
    if(newBox < 0) {
        newBox = 0;
    } else if((uint)newBox > theBox.howMuchBoxes - 1) {
        newBox = theBox.howMuchBoxes - 1;
    }

    if(moveCard != 0) {
        boxesCardCount[inWhichBox] = boxesCardCount[inWhichBox] - 1;
        boxesCardCount[newBox] = boxesCardCount[newBox] + 1;
    }

    QString htmlCodeForLabel;
    for(int i = 0; i < boxesCardCount.count(); i++) {
        QString boxCount = QString::number(boxesCardCount[i]);
        if(newBox == i) {
            htmlCodeForLabel.push_back("<u>" + boxCount + "</u> ");
        } else {
            htmlCodeForLabel.push_back(boxCount + " ");
        }
    }

    parentUi->cardStatsLabel->setText(htmlCodeForLabel);
}


QDataStream& operator<<(QDataStream& out, const box& v) {
    out << v.howMuchBoxes << v.boxes << v.againValue << v.hardValue << v.goodValue << v.easyValue << v.defaultSkipValue << v.startingBox;
    return out;
}
QDataStream& operator>>(QDataStream& in, box& v) {
    in >> v.howMuchBoxes;
    in >> v.boxes;
    in >> v.againValue;
    in >> v.hardValue;
    in >> v.goodValue;
    in >> v.easyValue;
    in >> v.defaultSkipValue;
    in >> v.startingBox;
    return in;
}

QDebug operator<<(QDebug dbg, const box& c) {
    dbg.nospace() << "box(howMuchBoxes=" << c.howMuchBoxes << ", boxes=" << c.boxes << ", againValue=" << c.againValue << ", hardValue=" << c.hardValue << ", goodValue=" << c.goodValue << ", easyValue=" << c.easyValue << ", defaultSkipValue=" << c.defaultSkipValue << ", startingBox=" << c.startingBox << ")";
    return dbg.space();
}

QDataStream& operator<<(QDataStream& out, const cardIndex& v) {
    out << v.index << v.skip;
    return out;
}
QDataStream& operator>>(QDataStream& in, cardIndex& v) {
    in >> v.index;
    in >> v.skip;
    return in;
}

QDebug operator<<(QDebug dbg, const cardIndex& c) {
    dbg.nospace() << "cardIndex(index=" << c.index << ", skip=" << c.skip << ")";
    return dbg.space();
}

