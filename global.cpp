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
QFile directories::globalSettings = directories::config.filePath("sanki.ini");
QString deckAddedFileName = "creationTime";

QString ereaderVars::model = "";
bool ereaderVars::inkboxUserApp = false;
QString ereaderVars::buttonNoFlashStylesheet = "QPushButton:pressed { background: white; color: black } QPushButton:checked { background: white; color: black } QPushButton { background: white; color: black }";
int ereaderVars::screenX = 1920;
int ereaderVars::screenY = 1080;

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

int checkBatteryLevel()
{
    // Only for the nia
    QFile batteryFile("/sys/devices/platform/pmic_battery.1/power_supply/mc13892_bat/capacity");
    QString batteryLevel;
    if(batteryFile.exists()) {
        batteryFile.open(QIODevice::ReadOnly);
        batteryLevel = batteryFile.readAll();
        batteryFile.close();
        return batteryLevel.trimmed().toInt();
    } else {
        return -1;
    }
}

void setBrightness(int value) {
    QString path = "/sys/class/backlight/mxc_msp430.0/brightness";
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << value;
        file.close();
    }
}

int getBrightness() {
    QFile file2("/sys/class/backlight/mxc_msp430.0/brightness");
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString contents = file2.readAll().trimmed();
        file2.close();
        return contents.toInt();
    }
    file2.close();
    return -1;
}
