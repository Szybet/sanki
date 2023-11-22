#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "mainMenu/sessions/sessionStruct.h"
#include "cardView/deckPlay.h"
#include "cardView/modes/boxes/boxes.h"

#include <QString>
#include <QDebug>
#include <QTextBrowser>
#include <QFile>
#include <QScrollBar>
#include <QDir>
#include <QSqlQuery>
#include <QRandomGenerator>

void splitMainCard(QString mainCard, QString* frontCard, QString* backCard, DeckPlay* parent);
void centerText(QTextBrowser* text);
void correctMainCard(QString* mainCard, QFile mediaFile);
void dumpScrollBarInfo(QScrollBar* scroll);
QString findDatabaseFile(QDir deckPath);
QString findMediaFile(card *acard, sessionStr *session);
QString cardExtract(card* acard, DeckPlay* parent); // Gets the actuall card content
uint randomValue(uint min, uint max);
QString adjustImgSize(uint width, QString text);

#endif // HELPERFUNCTIONS_H
