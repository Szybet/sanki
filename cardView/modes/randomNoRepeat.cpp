#include "randomNoRepeat.h"

#include <QDebug>
#include <QSqlQuery>

randomNoRepeat::randomNoRepeat(QObject *parent)
{
    Q_UNUSED(parent);
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

    QSqlQuery getIdQuery = db->exec("SELECT id FROM notes ORDER BY RANDOM()");

    while(getIdQuery.next()) {
        wholeList.push_back(getIdQuery.value(0).toULongLong());
    }

    qDebug() << "wholeList" << wholeList;

    loop();
}

void randomNoRepeat::loop() {


}

void randomNoRepeat::buttonClicked() {

}
