#include "mainMenu/mainWindow.h"
#include "global.h"
#include "mainMenu/sessions/sessionStruct.h"
#include "cardView/modes/boxes/boxes.h"
#include "components/other/infoDialog.h"

#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include <QLoggingCategory>
#include <QMessageBox>

bool enableDebug = false;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    switch (type) {
    case QtDebugMsg: {
        if(enableDebug == true) {
            if(context.line != 0) {
                fprintf(stderr, "Debug: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            } else {
                fprintf(stderr, "Debug: \"%s\"\n", localMsg.constData());
            }
        }
        break;
    }
    case QtInfoMsg: {


        if(ereader) {
            qDebug() << "Info dialog ereader mode";
            // Doesn't work ;/
            // msgBox.setFixedWidth(ereaderVars::screenX);
            infoDialog* infoDialogEreader = new infoDialog();
            infoDialogEreader->setModal(true);
            infoDialogEreader->show(); // Size and stuff
            infoDialogEreader->move(0, infoDialogEreader->y());
            infoDialogEreader->setFixedWidth(ereaderVars::screenX);
            infoDialogEreader->setText(localMsg.constData());
        } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText(localMsg.constData());
            msgBox.exec();
        }

        fprintf(stderr, "Info: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
    case QtWarningMsg: {

        fprintf(stderr, "Warning: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);

        if(warningsEnabled == true) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText(localMsg.constData());
            msgBox.exec();
        }

        break;
    }
    case QtCriticalMsg: {
        fprintf(stderr, "Critical: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(localMsg.constData());
        msgBox.exec();

        break;
    }
    case QtFatalMsg: {

        fprintf(stderr, "Fatal: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(localMsg.constData());
        msgBox.exec();

        break;
    }
    }
}

int main(int argc, char *argv[])
{
    if(qgetenv("DEBUG") == "true")
    {
        qDebug() << "Debug logs are enabled";
        enableDebug = true;
    } else {
#ifdef QT_DEBUG
        enableDebug = true;
        qDebug() << "Debug logs are disabled, but running a debug build, overwriting it";
#else
        QLoggingCategory::setFilterRules("qt.*=false");
#endif
    }

    if(qgetenv("SELF_MANAGE_DEBUG") != "true" && enableDebug == true) {
        QLoggingCategory::setFilterRules("qt.qpa.*=false\n"
                                         "qt.widgets.*=false\n"
                                         "qt.accessibility.*=false\n"
                                         "qt.text.*=false\n"
                                         "qt.gui.*=false\n"
                                         "qt.xkb.*=false");
    }

    // NOTE: won't work in 100% in release mode
    if(qgetenv("CUSTOM_DEBUG_FORMAT") != "false") {
        qDebug() << "Installing custom message handler";
        qInstallMessageHandler(myMessageOutput);
    }

    qDebug() << "Sanki started";
    // Warning: "QGuiApplication::platformFunction(): Must construct a QGuiApplication before accessing a platform function" (:0, )
    // because of that, disable warnings:
    warningsEnabled = false;
    QApplication a(argc, argv);

    // Detect platform
#ifdef PC
    pc = true;
    qDebug() << "Running platform: PC";
    warningsEnabled = true;
#endif

#ifdef EREADER
    ereader = true;
    qDebug() << "Running platform: ereader";
    checkEreaderModel();
    warningsEnabled = false; // fb plugin
#endif

    // For QSettings
    // Very important: After QApplication and before MainWindow
    // https://forum.qt.io/topic/142878/qvariant-unknown-user-type/6
    QCoreApplication::setApplicationName("Sanki");
    qRegisterMetaTypeStreamOperators<QList<QString>>("QList<QString>");
    qRegisterMetaTypeStreamOperators<DeckModes>("DeckModes");

    qRegisterMetaTypeStreamOperators<core>("core");
    qRegisterMetaTypeStreamOperators<times>("times");
    qRegisterMetaTypeStreamOperators<deckOptions>("deckOptions");
    qRegisterMetaTypeStreamOperators<card>("card");
    qRegisterMetaTypeStreamOperators<sessionStr>("sessionStr");

    qRegisterMetaTypeStreamOperators<box>("box");

    qRegisterMetaType<QList<QString>>("QList<QString>");
    qRegisterMetaType<DeckModes>("DeckModes");
    qRegisterMetaType<core>("core");
    qRegisterMetaType<times>("times");
    qRegisterMetaType<deckOptions>("deckOptions");
    qRegisterMetaType<card>("card");
    qRegisterMetaType<sessionStr>("sessionStr");

    qRegisterMetaType<box>("box");

    if(ereader) {
        // https://github.com/Szybet/niAudio/blob/main/apps-on-kobo/fix-special-characters-qt.md
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

        screenGeometry();

        a.setStyle("windows");
        QFile stylesheetFile("://other/eink.qss");
        stylesheetFile.open(QFile::ReadOnly);
        a.setStyleSheet(stylesheetFile.readAll());
        stylesheetFile.close();
        qDebug() << "Applied stylesheet for ereader";

        a.setCursorFlashTime(0);

        if(ereaderVars::inkboxUserApp == true && ereaderVars::nickelApp == true) {
            qCritical() << "Can't determine ereader OS";
        }

        if(ereaderVars::inkboxUserApp == true) {
            qDebug() << "App is a InkBox user app";
            directories::config = QDir("/app-data");
            directories::fileSelect = QDir("/app-data");
        } else if(ereaderVars::nickelApp == true) {
            qDebug() << "App is a Nickel app";
            directories::config = QDir("/mnt/onboard/.adds/sanki");
            directories::fileSelect = QDir("/mnt/onboard");
        } else {
            // Debug
            qDebug() << "App is in debug mode";
            directories::config = QDir("/sanki_debug_dir");
            directories::fileSelect = QDir("/"); // For now
        }
        directories::deckStorage = directories::config.path() + QDir::separator() + "decks";
        directories::sessionSaves = directories::config.path() + QDir::separator() + "sessions";
        directories::globalSettings.setFileName(directories::config.filePath("sanki.ini"));
    }

    MainWindow w;

    if(ereader) {
        w.setAnimated(false);
        w.showFullScreen();
        warningsEnabled = true;
    } else if(pc) {
        w.show();
    }

    if(directories::config.exists() == false) {
        QDir newDir; // Why variable is needed
        newDir.mkpath(directories::config.path());
    }

    qDebug() << "Deck storage path is" << directories::deckStorage;
    if(directories::deckStorage.exists() == false) {
        QDir newDir;
        newDir.mkpath(directories::deckStorage.path());
    }

    qDebug() << "Session saves path is" << directories::sessionSaves;
    if(directories::sessionSaves.exists() == false) {
        QDir newDir;
        newDir.mkpath(directories::sessionSaves.path());
    }

    return a.exec();
}
