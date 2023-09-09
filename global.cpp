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

#ifdef EREADER
#include "devicedescriptor.h"
#include "devbattery.h"
#include "devbrightness.h"
#endif

// Default values
bool debugEnabled = false;
bool warningsEnabled = true;

bool pc = false;
bool ereader = false;

QString deckAddedFileName = "creationTime";

namespace directories {
QDir config = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "sanki";
QDir deckStorage = directories::config.path() + QDir::separator() + "decks";
QDir sessionSaves = directories::config.path() + QDir::separator() + "sessions";
QDir fileSelect = QDir::homePath();
QFile globalSettings = directories::config.filePath("sanki.ini");
}

namespace ereaderVars {
bool inkboxUserApp = false;
bool nickelApp = false;
QString buttonNoFlashStylesheet = "QPushButton:pressed { background: white; color: black } QPushButton:checked { background: white; color: black } QPushButton { background: white; color: black }";
int screenX = 1920;
int screenY = 1080;
#ifdef EREADER
ereaderdev::device ereaderDevice;
#endif
}


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
#ifdef EREADER
    ereaderVars::ereaderDevice = ereaderdev::determineDevice();
    qDebug() << "Device model detected:" << ereaderdev::logDevice(&ereaderVars::ereaderDevice);
#endif
    QFile versionFile = QFile{"/mnt/onboard/.kobo/version"};
    if(versionFile.exists() == false) {
        qDebug() << "Unknown ereader device or in debug mode";
        return void();
    }

    ereaderVars::nickelApp = QDir("/mnt/onboard/.adds/kfmon/").exists();
    ereaderVars::inkboxUserApp = QDir("/app-data").exists();
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
#ifdef EREADER
    return getBatteryLevel(&ereaderVars::ereaderDevice);
#endif
    return -1;
}

void setWhiteBrightnessAlias(int value) {
#ifdef EREADER
    qDebug() << "Setting brightness...";
    setWhiteBrightness(&ereaderVars::ereaderDevice, value);
#endif
}

int getWhiteBrightnessAlias() {
#ifdef EREADER
    return getWhiteBrightness(&ereaderVars::ereaderDevice);
#endif
    return -1;
}

// Coppied from platform plugin
QString exec(const char *cmd)
{
    std::array<char, 128> buffer;
    QString result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result.trimmed();
}

bool createDir(QString absolutePath) {
    if(QDir(absolutePath).exists() == false) {
        bool status = QDir::root().mkpath(absolutePath);
        if(status == false) {
            qWarning() << "Failed to create directory:" << absolutePath;
        } else {
            qDebug() << "Created directory at path:" << absolutePath;
        }
        return status;
    }
    qDebug() << "Directory" << absolutePath << "Already exists";
    return true;
}
