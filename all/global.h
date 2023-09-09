#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QString>

#ifdef EREADER
#include "devicedescriptor.h"
#endif

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
    extern bool inkboxUserApp;
    extern bool nickelApp;
    extern QString buttonNoFlashStylesheet;
    extern int screenX;
    extern int screenY;
#ifdef EREADER
    extern ereaderdev::device ereaderDevice;
#endif
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
void setWhiteBrightnessAlias(int value);
int getWhiteBrightnessAlias();
QString exec(const char *cmd);
bool createDir(QString absolutePath);

#endif // GLOBALS_H