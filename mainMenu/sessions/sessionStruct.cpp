#include "mainMenu/sessions/sessionStruct.h"

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QDataStream>

QDataStream& operator<<(QDataStream& out, const core& v) {
    out << v.name << v.mode << v.deckPathList;
    return out;
}
QDataStream& operator>>(QDataStream& in, core& v) {
    in >> v.name;
    in >> v.mode;
    in >> v.deckPathList;
    return in;
}
QDataStream& operator<<(QDataStream& out, const times& v) {
    out << v.created << v.lastUsed << v.played << v.playedCount;
    return out;
}
QDataStream& operator>>(QDataStream& in, times& v) {
    in >> v.created;
    in >> v.lastUsed;
    in >> v.played;
    in >> v.playedCount;
    return in;
}
QDataStream& operator<<(QDataStream& out, const deckOptions& v) {
    out << v.inverted << v.pomodoro;
    return out;
}
QDataStream& operator>>(QDataStream& in, deckOptions& v) {
    in >> v.inverted;
    in >> v.pomodoro;
    return in;
}
QDataStream& operator<<(QDataStream& out, const card& v) {
    out << v.id << v.deckiD << v.count << v.againCount << v.hardCount << v.goodCount << v.easyCount;
    return out;
}
QDataStream& operator>>(QDataStream& in, card& v) {
    in >> v.id;
    in >> v.deckiD;
    in >> v.count;
    in >> v.againCount;
    in >> v.hardCount;
    in >> v.goodCount;
    in >> v.easyCount;
    return in;
}
QDataStream& operator<<(QDataStream& out, const sessionStr& v) {
    out << v.core << v.time << v.deckOptions << v.cardList;
    return out;
}
QDataStream& operator>>(QDataStream& in, sessionStr& v) {
    in >> v.core;
    in >> v.time;
    in >> v.deckOptions;
    in >> v.cardList;
    return in;
}

QDebug operator<<(QDebug dbg, const core& c) {
    dbg.nospace() << "core(name=" << c.name << ", mode=" << c.mode << ", deckPathList=" << c.deckPathList << ")";
    return dbg.space();
}

QDebug operator<<(QDebug dbg, const times& t) {
    dbg.nospace() << "times(created=" << t.created.toString() << ", lastUsed=" << t.lastUsed.toString() << ", played=" << t.played.toString() << ")";
    return dbg.space();
}

QDebug operator<<(QDebug dbg, const deckOptions& c) {
    dbg.nospace() << "cards(inverted=" << c.inverted << ", pomodoro=" << c.pomodoro << ")";
    return dbg.space();
}

QDebug operator<<(QDebug dbg, const card& c) {
    dbg.nospace() << "card(id=" << c.id << ", deckiD=" << c.deckiD << ", count=" << c.count << ", againCount=" << c.againCount << ", hardCount=" << c.hardCount << ", goodCount=" << c.goodCount << ", easyCount=" << c.easyCount << ")";
    return dbg.space();
}

QDebug operator<<(QDebug dbg, const sessionStr& s) {
    dbg.nospace() << "sessionStr(core=" << s.core << ", time=" << s.time << ", cards=" << s.deckOptions << ", cardList=" << s.cardList << ")";
    return dbg.space();
}

// https://stackoverflow.com/questions/18144377/writing-and-reading-custom-class-to-qsettings
// Doesn't work, going the easy way
/*
QMap<QString, QVariant> sessionStrToMap(const sessionStr session)
{
    QMap<QString, QVariant> map;
    map.insert("core/name", session.core.name);
    map.insert("core/mode", static_cast<int>(session.core.mode));
    map.insert("core/deckPathList", QVariant::fromValue(session.core.deckPathList));
    map.insert("time/created", session.time.created);
    map.insert("time/lastUsed", session.time.lastUsed);
    map.insert("time/played", session.time.played);
    map.insert("cards/played", session.cards.played);
    map.insert("cards/inverted", session.cards.inverted);
    map.insert("cards/totalCards", session.cards.totalCards);
    return map;
}

// Convert QMap<QString, QVariant> to sessionStr struct
sessionStr mapToSessionStr(const QMap<QString, QVariant> map)
{
    sessionStr session;
    session.core.name = map.value("core/name").toString();
    session.core.mode = static_cast<DeckModes>(map.value("core/mode").toInt());
    session.core.deckPathList = map.value("core/deckPathList").value<QList<QString>>();
    session.time.created = map.value("time/created").toDateTime();
    session.time.lastUsed = map.value("time/lastUsed").toDateTime();
    session.time.played = map.value("time/played").toTime();
    session.cards.played = map.value("cards/played").toUInt();
    session.cards.inverted = map.value("cards/inverted").toBool();
    session.cards.totalCards = map.value("cards/totalCards").toUInt();
    return session;
}
*/
