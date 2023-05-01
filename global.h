#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QString>

extern bool debugEnabled;

// Those variables check if it's running on this device
extern bool pc;
extern bool ereader;

namespace directories {
    extern QDir config;
    extern QDir deckStorage;
    extern QDir sessionSaves;
    extern QDir deckSelect; // File chooser will open here
}

namespace ereaderVars {
    extern QString model;
    extern bool running_on_kobo;
    extern int screen_x;
    extern int screen_y;
    extern int batt_level_int;
}

enum DeckModes {
    None,
    CompletlyRandomised,
    RandomisedNoRepeating,
};
Q_DECLARE_METATYPE(DeckModes);

void check_device();
void screen_geometry();
void check_battery_level();
void set_brightness(int value);
int get_brightness();

#endif // GLOBALS_H
