#include "completlyRandom.h"
#include "cardView/deckPlay.h"
#include "ui_deckPlay.h"
#include "cardView/buttons/showCard.h"
#include "cardView/functions/helperFunctions.h"

#include <QObject>
#include <QSqlQuery>
#include <QDebug>

CompletlyRandom::CompletlyRandom(QObject *parent)
{
    qDebug() << parent->objectName();
}

void CompletlyRandom::setup(DeckPlay* parentArg, Ui::DeckPlay* parentUiArg) {
    parent = parentArg;
    parentUi = parentUiArg;
    frontText = parentUi->textFrontCard;
    backText = parentUi->textBackCard;

    // Setup show/next card button
    showCard* showCardWidget = new showCard(parentArg);

    connect(showCardWidget, &showCard::clicked, this, &CompletlyRandom::buttonClicked); // Button slot
    connect(this, &CompletlyRandom::setText, showCardWidget, &showCard::setText);

    parentUi->gridManageCard->addWidget(showCardWidget);

    max = parent->currectSession.cardList.count() - 1;
    qDebug() << "max:" << max;

    loop();
}

// nextCardCall
void CompletlyRandom::loop()
{
    parentUi->lineMiddleText->setVisible(false);
    card* randomCard = &parent->currectSession.cardList[randomValue(0, max)];
    randomCard->count += 1;

    QString deckName = parent->currectSession.core.deckPathList[randomCard->deckiD];
    deckName = deckName.split("/").last();
    qDebug() << "Deck name for card:" << deckName;
    if(deckName.length() > 20) {
        deckName = deckName.left(20);
        deckName.append("...");
    }
    parent->changeStatusBarTextSlot(deckName);

    qDebug() << "random card:" << randomCard;

    QString mainCard = cardExtract(randomCard, parent);

    correctMainCard(&mainCard, findMediaFile(randomCard, &parent->currectSession));
    splitMainCard(mainCard, &frontCard, &backCard);

    QString searchPath = directories::deckStorage.filePath(parent->currectSession.core.deckPathList[randomCard->deckiD]);
    frontText->setSearchPaths(QStringList(searchPath));
    backText->setSearchPaths(QStringList(searchPath));

    parent->resetScrollState();

    backText->hide();
    parent->setText(frontText, frontCard);
}

void CompletlyRandom::buttonClicked()
{
    qDebug() << "buttonClicked";
    if (showedBack == false)
    {
        qDebug() << "showedBack = false";
        parentUi->lineMiddleText->setVisible(true);
        showedBack = true;
        backText->show();
        parent->setText(backText, backCard);

        // buttonWidget->setText("Next");
        // Idk, crashes on it - will use a signal
        emit setText("Next");
    }
    else
    {
        showedBack = false;
        emit setText("Show");
        backText->clear();
        parent->firstLaunch = false;
        loop();
    }
}

