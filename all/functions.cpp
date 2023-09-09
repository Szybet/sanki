#include "functions.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <fstream>
#include <QDir>
#include <QProcess>
#include <regex>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <QDateTime>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QNetworkInterface>
#include <QMutex>

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

void log(QString message, QString className, bool applicationStart) {
    qDebug() << message;
}

bool writeFile(QString filename, QString content) {
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << content;
        return true;
    }
    else {
        QString function = __func__; log(function + ": Failed to write string '" + content + "' to file '" + filename + "'", "functions");
        return false;
    }
}

QString readFile(QString file) {
    if(QFile::exists(file)) {
        QFile fileToRead(file);
        fileToRead.open(QIODevice::ReadOnly);
        QTextStream in (&fileToRead);
        QString content = in.readAll();
        return content;
    }
    else {
        return NULL;
    }
}
