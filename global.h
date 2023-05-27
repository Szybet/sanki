#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QString>

extern bool debugEnabled;
extern bool warningsEnabled;

// Those variables check if it's running on this device
extern bool pc;
extern bool ereader;

namespace directories {
    extern QDir config;
    extern QDir deckStorage;
    extern QDir sessionSaves;
    extern QDir fileSelect; // File chooser will open here
    extern QFile globalSettings;
}
extern QString deckAddedFileName;

namespace ereaderVars {
    extern QString model;
    extern bool inkboxUserApp;
    extern QString buttonNoFlashStylesheet;
    extern int screenX;
    extern int screenY;
}

enum DeckModes {
    None,
    CompletlyRandomised,
    RandomisedNoRepeating,
    Boxes,
};
Q_DECLARE_METATYPE(DeckModes);

bool renameDir(QDir & dir, const QString & newName);
void checkEreaderModel();
void screenGeometry();
int checkBatteryLevel();
void setBrightness(int value);
int getBrightness();

#endif // GLOBALS_H
