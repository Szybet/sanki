#include "completlyRandom.h"
#include "cardView/deckPlay.h"
#include "qdebug.h"
#include "ui_deckPlay.h"
#include "cardView/showCard.h"

#include <qobject.h>
#include <QSqlQuery>

CompletlyRandom::CompletlyRandom(QObject *parent)
{
    qDebug() << parent->objectName();
}

void CompletlyRandom::setup(DeckPlay* parentArg, Ui::DeckPlay* parentUiArg, QSqlDatabase *dbArg) {
    parent = parentArg;
    parentUi = parentUiArg;
    db = dbArg;

    // Setup show/next card button
    showCard* showCardWidget = new showCard(parentArg);

    connect(showCardWidget, &showCard::clicked, this, &CompletlyRandom::buttonClicked); // Button slot
    connect(this, &CompletlyRandom::setText, showCardWidget, &showCard::setText);

    parentUiArg->gridManageCard->addWidget(showCardWidget);

    frontText = parentUi->textFrontCard;
    backText = parentUi->textBackCard;

    loop();
}

// nextCardCall
void CompletlyRandom::loop()
{
    QSqlQuery queryId = db->exec("SELECT id FROM notes ORDER BY RANDOM() LIMIT 1");
    queryId.next();

    // its too big for int + no need for a number
    QString idStr = queryId.value(0).toString(); // random id

    // set variables
    QString mainCardSql = "SELECT flds FROM notes WHERE id=" + idStr;

    QSqlQuery MainCardQuery = db->exec(mainCardSql);
    MainCardQuery.next();
    mainCard = MainCardQuery.value(0).toString();

    // Parse the text
    parent->correctString(&mainCard);
    parent->splitMainCard(mainCard, &frontCard, &backCard);

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
