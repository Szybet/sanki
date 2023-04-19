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
    frontText->setText(frontCard);

    // Very important
    frontText->document()->adjustSize();

    // This fixes the issue that after adding text it is cutted in half
    // Doesn't work ui->textFrontCard->verticalScrollBar()->setSliderPosition(0);
    frontText->verticalScrollBar()->setValue(0);

    parent->centerText(frontText);
}

void CompletlyRandom::buttonClicked()
{
    qDebug() << "buttonClicked";
    if (showedBack == false)
    {
        qDebug() << "showedBack = false";
        showedBack = true;
        backText->show();
        backText->setText(backCard);
        backText->document()->adjustSize();

        backText->verticalScrollBar()->setValue(0);
        parent->centerText(backText);

        // buttonWidget->setText("Next");
        // Idk, crashes on it - will use a signal
        emit setText("Next");
    }
    else
    {
        showedBack = false;
        emit setText("Show");
        backText->clear();
        loop();
    }
}
