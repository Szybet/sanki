#include "randomNoRepeat.h"

randomNoRepeat::randomNoRepeat(QObject *parent)
{

}

void randomNoRepeat::setup(DeckPlay* parentArg, Ui::DeckPlay* parentUiArg, QSqlDatabase *dbArg) {
    parent = parentArg;
    parentUi = parentUiArg;
    db = dbArg;

    // Setup show/next card button
    showCard* showCardWidget = new showCard(parentArg);

    connect(showCardWidget, &showCard::clicked, this, &randomNoRepeat::buttonClicked); // Button slot
    connect(this, &randomNoRepeat::setText, showCardWidget, &showCard::setText);

    parentUiArg->gridManageCard->addWidget(showCardWidget);

    frontText = parentUi->textFrontCard;
    backText = parentUi->textBackCard;

    loop();
}

void randomNoRepeat::loop() {


}

void randomNoRepeat::buttonClicked() {

}
