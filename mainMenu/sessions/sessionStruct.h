#ifndef SESSIONSTRUCT_H
#define SESSIONSTRUCT_H

#include "global.h"

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QDataStream>

// https://stackoverflow.com/questions/18144377/writing-and-reading-custom-class-to-qsettings
struct core {
    QString name; // Name of the session - the same as the file name
    DeckModes mode = None; // Mode of the session
    QList<QString> deckPathList; // List of decks in the session - order is important because of Id's in card
};
Q_DECLARE_METATYPE(core);

struct times {
    QDateTime created = QDateTime::currentDateTime(); // When the session was created
    QDateTime lastUsed = QDateTime::currentDateTime(); // When the session was last used
    quint64 played = 0; // For how long was it used
    uint playedCount = 0; // How many times was the deck "entered" and played for more than 2 minutes
};
Q_DECLARE_METATYPE(times);

struct deckOptions {
    bool inverted = false;
    bool pomodoro = false;
};
Q_DECLARE_METATYPE(deckOptions);

struct card {
    quint64 id = 0; // Id in the database - ulong has problems, idk
    uint deckiD = 0; // Id from core::deckPathList
    uint count = 0; // How many times this card appeared before

    // Things for boxes mode
    uint againCount = 0; // How many times the again button was clicked on this card
    uint hardCount = 0;
    uint goodCount = 0;
    uint easyCount = 0;
};
Q_DECLARE_METATYPE(card);

struct sessionStr {
    struct core core;
    struct times time;
    struct deckOptions deckOptions;
    QList<card> cardList;
};
Q_DECLARE_METATYPE(sessionStr)

QString getSmallStatsForSession(sessionStr session, bool lastUsed);
QString getStatsForSession(sessionStr session, bool lastUsed, bool creationTime = true, bool showFullInfo = false);

extern QDebug operator<<(QDebug dbg, const core& c);
extern QDebug operator<<(QDebug dbg, const times& t);
extern QDebug operator<<(QDebug dbg, const deckOptions& c);
extern QDebug operator<<(QDebug dbg, const card& c);
extern QDebug operator<<(QDebug dbg, const sessionStr& s);

extern QDataStream& operator<<(QDataStream& out, const core& v);
extern QDataStream& operator>>(QDataStream& in, core& v);
extern QDataStream& operator<<(QDataStream& out, const times& v);
extern QDataStream& operator>>(QDataStream& in, times& v);
extern QDataStream& operator<<(QDataStream& out, const deckOptions& v);
extern QDataStream& operator>>(QDataStream& in, deckOptions& v);
extern QDataStream& operator<<(QDataStream& out, const card& v);
extern QDataStream& operator>>(QDataStream& in, card& v);
extern QDataStream& operator<<(QDataStream& out, const sessionStr& v);
extern QDataStream& operator>>(QDataStream& in, sessionStr& v);

#endif // SESSIONSTRUCT_H
