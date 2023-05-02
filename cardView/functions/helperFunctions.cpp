#include "cardView/functions/helperFunctions.h"

void splitMainCard(QString mainCard, QString* frontCard, QString* backCard) {
    // mainCard is:
    // frontCard + this character https://unicode-table.com/en/001F/ + backCard
    QStringList cards = mainCard.split("\u001F");
    qDebug() << "cards splitted are: " << cards;

    *frontCard = cards.first();
    *backCard = cards.last();

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
            }
        }
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
        qWarning() << "Only old version of the database was found for deck" << deckPath.dirName() << "\npropably this will cause problems";
        return collection2.fileName();
    } else {
        QString message = "No supported collection file was found in this deck: " + deckPath.dirName() + "\nIt is probably too new and has not been tested.";
        qFatal("%s", message.toStdString().c_str());
    }
}

QString findMediaFile(card* acard, sessionStr* session) {
    QString mediaFile = directories::deckStorage.filePath(session->core.deckPathList[acard->deckiD]) + QDir::separator() + "media";
    if(QFile(mediaFile).exists() == true) {
        return mediaFile;
    } else {
        qCritical() << "Media file doesn't found for deck at:" << mediaFile;
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
        qCritical() << "Failed to find card content:" << &acard;
    }

}

uint randomValue(uint min, uint max) {
    return QRandomGenerator::global()->generate() % (max - min + 1) + min;
}
