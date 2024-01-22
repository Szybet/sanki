#include "cardView/functions/helperFunctions.h"

#include <QRegularExpression>

void splitMainCard(QString mainCard, QString* frontCard, QString* backCard, DeckPlay* parent) {
    // mainCard is:
    // frontCard + this character https://unicode-table.com/en/001F/ + backCard
    QStringList cards = mainCard.split("\u001F");
    qDebug() << "cards splitted are: " << cards;

    if(parent->reversedCards == false) {
        *frontCard = cards.first();
        *backCard = cards.last();
    } else {
        *frontCard = cards.last();
        *backCard = cards.first();
    }

    qDebug() << "frontCard is: " << *frontCard;
    qDebug() << "backCard is: " << *backCard;
}

void centerText(QTextBrowser* text) {
    // This isEmpty() needs to be done after setText becouse it will Segment fault
    if(text->document()->isEmpty() == false)
    {
        text->selectAll();
        text->setAlignment(Qt::AlignCenter);

        // This removes selection
        QTextCursor cursor = text->textCursor();
        cursor.clearSelection();
        text->setTextCursor(cursor);
    }
}

bool containsBook(QString str) {
    if(str.contains(".epub") || str.contains(".pdf") || str.contains(".txt")) {
        return true;
    } else {
        return false;
    }
}

void correctMainCard(QString* mainCard, QFile mediaFile)
{
    // turn those weird image id's to file names
    // this is a json file, but a weird one so...
    // TODO: In the future this needs to be done using json parsing.
    if(mainCard->contains("<img src="))
    {
        mediaFile.open(QIODevice::ReadOnly);
        QString mediaContent = mediaFile.readAll();
        mediaFile.close();

        mediaContent = mediaContent.replace("{", "");
        mediaContent = mediaContent.replace("}", "");

        // This is impossible becouse of:  "7": "rew-zasada lewej 1.png"
        // media_contend = media_contend.replace(" ", "");
        // for now this:
        mediaContent = mediaContent.replace(": ", ":");
        mediaContent = mediaContent.replace(", ", ",");

        QStringList split_dot = mediaContent.split(",");
        for(const QString &item: split_dot)
        {
            mediaContent = mediaContent.replace("\"", "");

            qDebug() << "item is: " << item;

            QStringList replace_items = item.split(":");
            if(mainCard->contains(replace_items.last()))
            {
                qDebug() << "mainCard contains items_last";
                mainCard = &mainCard->replace(replace_items.last(), replace_items.first());
                QString lastItem = replace_items.last();
                if(containsBook(lastItem)) {
                    qDebug() << "It contains a book, detected in json handling";
                    QString last = replace_items.last();
                    QString first = replace_items.first();
                    last.chop(1);
                    first.remove(0, 1);
                    QString newLink = last + BOOK_LINK_SPLIT + first;
                    qDebug() << "newLink:" << newLink;

                    mainCard = &mainCard->replace(replace_items.first(), newLink);
                }
            }
        }
    }

    if(containsBook(*mainCard)) {
        qDebug() << "This card contains a book" << *mainCard;

        QStringList splittedhtml = mainCard->split("<");
        QString tmpCard = splittedhtml.first();
        splittedhtml.removeFirst();
        foreach(QString str, splittedhtml) {
            if(str.startsWith("img")) {
                if(containsBook(str)) {
                    qDebug() << "Detected in in img";
                    QStringList split2 = str.split(">");
                    QString newStr = split2.first().replace("img src=\"", "");

                    while(newStr.endsWith(">") || newStr.endsWith(" ") || newStr.endsWith("\"")) {
                        qDebug() << "Removing...";
                        newStr.chop(1);
                    }
                    qDebug() << "Clear link is:" << newStr;

                    tmpCard.append("<a href=\"" + newStr + "\">" + newStr.split(BOOK_LINK_SPLIT).first() + "</a>" + split2.last());
                } else {
                    tmpCard.append("<" + str);
                }
            } else {
                tmpCard.append("<" + str);
            }
        }
        *mainCard = tmpCard;
        qDebug() << "Final link:" << *mainCard;
    }

    // Weird: &nbsp; ( hard space in html ) sometimes doesn't get parsed
    mainCard = &mainCard->replace("&nbsp;", " ");
    Q_UNUSED(mainCard);

    // Add a line at the end becouse one line is cutted out...
    // mainCard->append("<br>");
    // On reader fixed cutted off line
    // Causes problem with scroll appearing
}

void dumpScrollBarInfo(QScrollBar* scroll) {
    if (scroll) {
        if(false) {
            qDebug() << "ScrollBar - Object Name: " << scroll->objectName()
                     << ", Minimum value: " << scroll->minimum()
                     << ", Maximum value: " << scroll->maximum()
                     << ", Page step: " << scroll->pageStep()
                     << ", Single step: " << scroll->singleStep()
                     << ", Value: " << scroll->value()
                     << ", Slider position: " << scroll->sliderPosition();
        }
    } else {
        qDebug() << "ScrollBar - Object Name: NULL";
    }
}

QString findDatabaseFile(QDir deckPath) {
    // Support for this newer anki database...
    QFile collection21 = deckPath.filePath("collection.anki21");
    QFile collection2 = deckPath.filePath("collection.anki2");

    if(collection21.exists() == true)
    {
        qDebug() << "Returning:" << collection21.fileName();
        return collection21.fileName();
    } else if(collection2.exists() == true) {
        qDebug() << "Returning:" << collection2.fileName();
        // Actually important debug
        qDebug() << "Only old version of the database was found for deck" << deckPath.dirName() << "propably this will cause problems";
        return collection2.fileName();
    } else {
        QString message = "No supported collection file was found in this deck: " + deckPath.dirName() + "<br>It is probably too new and has not been tested, <strong>Or the deck is missing</strong>";
        qWarning() << message;
        return "none";
    }
}

QString findMediaFile(card* acard, sessionStr* session) {
    QString mediaFile = directories::deckStorage.filePath(session->core.deckPathList[acard->deckiD]) + QDir::separator() + "media";
    if(QFile(mediaFile).exists() == true) {
        return mediaFile;
    } else {
        qWarning() << "Media file doesn't found for deck at:" << mediaFile;
    }
    return QString(); // Supress warning
}

QString cardExtract(card* acard, DeckPlay* parent) {
    QSqlQuery query("SELECT flds FROM notes WHERE id = :id", parent->realSqlDatabases[acard->deckiD]);
    query.bindValue(0, acard->id);
    if(query.exec()) {
        query.next();
        return query.value(0).toString();
    } else {
        qWarning() << "Failed to find card content:" << &acard;
    }
    return "";
}

uint randomValue(uint min, uint max) {
    return QRandomGenerator::global()->generate() % (max - min + 1) + min;
}

// Regex magician needed
QString adjustImgSize(uint width, QString text) {
    qDebug() << "Original text:" << text << "provided width:" << width;

    // Remove width and height tags at all
    // \b(?:width|height)\s*=\s*"\d+"\s*
    static QRegularExpression pattern("\\b(?:width|height)\\s*=\\s*\"\\d+\"\\s*");
    QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(text);

    text = text.remove(pattern);

    // Output the result
    qDebug() << "Removed tags: " << text;

    //QString sizes = "<img height=\"" + QString::number(height) + "\" width=\"" + QString::number(width) + "\"";
    QString sizes = "<img width=\"" + QString::number(width) + "\"";
    qDebug() << "Sizes:" << sizes;
    text = text.replace("<img", sizes);

    qDebug() << "Modified sizes:" << text;

    return text;
}
