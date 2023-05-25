#include <global.h>

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QTextCodec>
#include <QStandardPaths>

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
// https://stackoverflow.com/questions/61735609/implicit-instantiation-of-undefined-template-std-1basic-istringstreamchar
#include <sstream>
// https://stackoverflow.com/questions/1057287/ofstream-error-in-c
#include <fstream>

// Default values
bool debugEnabled = false;
bool warningsEnabled = true;

bool pc = false;
bool ereader = false;

QDir directories::config = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "sanki";
QDir directories::deckStorage = directories::config.path() + QDir::separator() + "decks";
QDir directories::sessionSaves = directories::config.path() + QDir::separator() + "sessions";
QDir directories::fileSelect = QDir::homePath();
QString deckAddedFileName = "creationTime";

QString ereaderVars::model = "";
bool ereaderVars::inkboxUserApp = false;
int ereaderVars::screenX = 1920;
int ereaderVars::screenY = 1080;
int ereaderVars::batteryLevel = 100;

bool renameDir(QDir & dir, const QString & newName) {
    // https://stackoverflow.com/questions/39229177/qdirrename-redundant-parameters
    auto src = QDir::cleanPath(dir.filePath("."));
    auto dst = QDir::cleanPath(
        dir.filePath(QStringLiteral("..%1%2").arg(QDir::separator()).arg(newName)));
    auto rc = QFile::rename(src, dst);
    if (rc) dir.setPath(dst);
    return rc;
}

void checkEreaderModel()
{
    QFile versionFile = QFile{"/mnt/onboard/.kobo/version"};
    if(versionFile.exists() == false) {
        qDebug() << "Unknown ereader device or in debug mode";
        return void();
    }
    versionFile.open(QIODevice::ReadOnly);
    ereaderVars::model = versionFile.readAll().replace("\n", "");
    versionFile.close();
    qDebug() << "Sanki is running on a kobo:" << ereaderVars::model;

    if(ereaderVars::model.length() > 6) {
        ereaderVars::inkboxUserApp = false;
    } else {
        ereaderVars::inkboxUserApp = true;
    }
}


// Ereader mainly
void screenGeometry()
{
    QRect screenGeometry = QGuiApplication::screens()[0]->geometry();
    ereaderVars::screenX = screenGeometry.width();
    ereaderVars::screenY = screenGeometry.height();
    qDebug() << "Screen size is x:" << ereaderVars::screenX << "y:" << ereaderVars::screenY;
}

void check_battery_level()
{
    // Copied from inkbox
    QFile batt_level_file("/sys/devices/platform/pmic_battery.1/power_supply/mc13892_bat/capacity");
    QString batt_level;
    if(batt_level_file.exists()) {
        batt_level_file.open(QIODevice::ReadOnly);
        batt_level = batt_level_file.readAll();
        batt_level = batt_level.trimmed();

        //QString message = "Battery level is: ";
        //message.append(batt_level);
        //debugLog(message, "globals.h", "check_battery_level");

        ereaderVars::batteryLevel = batt_level.toInt();
        batt_level_file.close();
    }
    else {
        ereaderVars::batteryLevel = 100;
    }
}
void set_brightness(int value) {
    // doesnt work
    std::ofstream fhandler;
    fhandler.open("/var/run/brightness");
    fhandler << value;
    fhandler.close();
}

int get_brightness() {
    // doesnt work
    QFile brightness("/var/run/brightness");
    brightness.open(QIODevice::ReadOnly);
    QString valuestr = brightness.readAll();
    int value = valuestr.toInt();
    brightness.close();
    return value;
    return 0;
}
