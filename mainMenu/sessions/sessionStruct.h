#ifndef SESSIONSTRUCT_H
#define SESSIONSTRUCT_H

#include "global.h"

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QDataStream>

// https://stackoverflow.com/questions/18144377/writing-and-reading-custom-class-to-qsettings
struct core {
    QString name;
    DeckModes mode = None;
    QList<QString> deckPathList;
};
Q_DECLARE_METATYPE(core);

struct times {
    QDateTime created = QDateTime::currentDateTime();
    QDateTime lastUsed = QDateTime::currentDateTime();
    QTime played = QTime();
};
Q_DECLARE_METATYPE(times);

struct cards {
    uint played = 0;
    bool inverted = false;
    uint totalCards = 0;
};
Q_DECLARE_METATYPE(cards);

struct sessionStr {
    struct core core;
    struct times time;
    struct cards cards;
};
Q_DECLARE_METATYPE(sessionStr)

extern QDebug operator<<(QDebug dbg, const core& c);
extern QDebug operator<<(QDebug dbg, const times& t);
extern QDebug operator<<(QDebug dbg, const cards& c);
extern QDebug operator<<(QDebug dbg, const sessionStr& s);

extern QDataStream& operator<<(QDataStream& out, const core& v);
extern QDataStream& operator>>(QDataStream& in, core& v);
extern QDataStream& operator<<(QDataStream& out, const times& v);
extern QDataStream& operator>>(QDataStream& in, times& v);
extern QDataStream& operator<<(QDataStream& out, const cards& v);
extern QDataStream& operator>>(QDataStream& in, cards& v);
extern QDataStream& operator<<(QDataStream& out, const sessionStr& v);
extern QDataStream& operator>>(QDataStream& in, sessionStr& v);

#endif // SESSIONSTRUCT_H
