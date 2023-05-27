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
    dbg.nospace() << "times(created=" << t.created.toString() << ", lastUsed=" << t.lastUsed.toString() << ", played=" << t.played << ")";
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

QString getStatsForSession(sessionStr session, bool lastUsed, bool creationTime, bool showFullInfo) {
    //QString returnStr = "<p align=\"center\">";
    QString returnStr;

    QString mode;
    // No better no problematic way
    if(session.core.mode == CompletlyRandomised) {
        mode = "Completly Randomised";
    } else if(session.core.mode == Boxes) {
        mode = "Boxes";
    }

    returnStr = returnStr + "<b>Mode:</b> " + mode + "<br>";
    QStringList decks;
    foreach(QString path, session.core.deckPathList) {
        decks.append(path.split("/").last());
    }
    QString decksString = decks.join(", ");
    if(showFullInfo == false && decksString.length() > 41) {
        decksString = decksString.left(40);
        decksString.append("...");
    }

    returnStr = returnStr + "<b>Decks:</b> " + decksString + "<br>";
    if(creationTime == true) {
        returnStr = returnStr + "<b>Created:</b> " + session.time.created.toString("dd.MM.yyyy - hh:mm") + "<br>";
    }
    if(lastUsed) {
        returnStr = returnStr + "<b>Last used:</b> " + session.time.lastUsed.toString("dd.MM.yyyy - hh:mm") + "<br>";
    }

    // Thereotical 24h limit?
    QTime timeTemp = QTime::fromString("0:0:0", "h:m:s");
    qDebug() << "session->time.played:" << session.time.played;
    QTime realTime = timeTemp.addMSecs(session.time.played);
    qDebug() << "realTime:" << realTime.second();
    qDebug() << "timeTemp:" << timeTemp.second();

    QString hours = QString::number(realTime.hour());
    QString minutes = QString::number(realTime.minute());
    QString seconds = QString::number(realTime.second());

    if(hours.count() == 1) {
        hours = "0" + hours;
    }
    if(minutes.count() == 1) {
        minutes = "0" + minutes;
    }
    if(seconds.count() == 1) {
        seconds = "0" + seconds;
    }

    qDebug() << "Played time:" << session.time.played << "hours:" << hours << "minutes:" << minutes << "seconds:" << seconds;

    returnStr = returnStr + "<b>Time spend:</b> " + hours + ":" + minutes + ":" + seconds + "<br>";

    returnStr = returnStr + "<b>How many times used:</b> " + QString::number(session.time.playedCount) + "<br>";
    if(QString::number(session.cardList.count()) != 0) {
        returnStr = returnStr + "<b>Total cards:</b> " + QString::number(session.cardList.count()) + "<br>";
    }

    //returnStr.push_back("</p>");
    return returnStr;
}

QString getSmallStatsForSession(sessionStr session, bool lastUsed) {
    QString returnStr = "<p align=\"center\">";

    QString mode;
    // No better no problematic way
    if(session.core.mode == CompletlyRandomised) {
        mode = "Completly Randomised";
    } else if(session.core.mode == Boxes) {
        mode = "Boxes";
    }

    returnStr = returnStr + mode + "<br>";
    QStringList decks;
    foreach(QString path, session.core.deckPathList) {
        decks.append(path.split("/").last());
    }
    QString decksString = decks.join(", ");
    if(decksString.length() > 41) {
        decksString = decksString.left(40);
        decksString.append("...");
    }
    returnStr = returnStr + decksString + "<br>";

    if(lastUsed) {
        returnStr = returnStr + session.time.lastUsed.toString("dd.MM.yyyy - hh:mm") + "<br>";
    }

    // Thereotical 24h limit?
    QTime timeTemp = QTime::fromString("0:0:0", "h:m:s");
    qDebug() << "session->time.played:" << session.time.played;
    QTime realTime = timeTemp.addMSecs(session.time.played);
    qDebug() << "realTime:" << realTime.second();
    qDebug() << "timeTemp:" << timeTemp.second();

    QString hours = QString::number(realTime.hour());
    QString minutes = QString::number(realTime.minute());
    QString seconds = QString::number(realTime.second());

    if(hours.count() == 1) {
        hours = "0" + hours;
    }
    if(minutes.count() == 1) {
        minutes = "0" + minutes;
    }
    if(seconds.count() == 1) {
        seconds = "0" + seconds;
    }

    qDebug() << "Played time:" << session.time.played << "hours:" << hours << "minutes:" << minutes << "seconds:" << seconds;

    returnStr = returnStr + hours + ":" + minutes + ":" + seconds + "<br>";

    returnStr = returnStr + QString::number(session.time.playedCount) + "<br>";
    if(QString::number(session.cardList.count()) != 0) {
        returnStr = returnStr + QString::number(session.cardList.count()) + "<br>";
    }

    returnStr.push_back("</p>");
    return returnStr;
}
