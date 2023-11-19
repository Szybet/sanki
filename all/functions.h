#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

// I hope in the future this file in sanki won't be needed
namespace global {
    namespace audio {
        inline bool enabled = false;
        struct musicFile {
            QString path;
            QString name; // Cut path for easier use in names
            int lengths; // length Seconds
            QString length; // In minutes:seconds
            int id;
        };
        // 'None' is when 'currentAction' is empty
        enum class Action { // Function will be called with this enum
            Play,
            Next,
            Previous,
            Pause,
            Continue,
            Stop, // Sets 'paused' to false, 'isSomethingCurrentlyPlaying' to false, and 'itemCurrentlyPlaying' to -1; also stops playing
            SetVolume,
            };
        inline QVector<Action> currentAction;
        inline QVector<musicFile> queue;
        inline QVector<musicFile> fileList;
        inline int itemCurrentlyPlaying = -1; // Also indicates in the queue menu which a gray color which is playing
        inline QMutex audioMutex; // These variables will be shared between threads, so here, it's to protect it
        inline int progressSeconds = -5; // -5 at default to avoid cutting song too early... yea
        inline bool paused = false;
        inline bool isSomethingCurrentlyPlaying = false; // Pause and continue
        inline bool firstScan = true;
        inline int volumeLevel = 40; // Default save value
        inline bool songChanged = false;
    }
}

void log(QString message, QString className = "undefined", bool applicationStart = false);
bool writeFile(QString filename, QString content);
QString readFile(QString file);

#endif // FUNCTIONS_H
