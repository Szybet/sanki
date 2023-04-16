#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QString>

extern bool debug_enabled;
namespace directories {
    extern QDir work_dir;
    extern QDir deck_storage;
}
extern QString kobo_model;
extern bool running_on_kobo;
extern int screen_x;
extern int screen_y;
extern int batt_level_int;

void check_device();
void debugLog(QString Message, QString file, QString function);
void screen_geometry();
void check_battery_level();
void set_brightness(int value);
int get_brightness();

#endif // GLOBALS_H
