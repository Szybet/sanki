#include "mainMenu/mainWindow.h"
#include "global.h"
#include "mainMenu/sessions/sessionStruct.h"
#include "cardView/modes/boxes/boxes.h"
#include "components/other/infoDialog.h"

#ifdef EREADER
#include "audiothread.h"
#endif

#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include <QLoggingCategory>
#include <QMessageBox>
#include <QThread>

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGesture>

#include "components/other/reImplementations/qGraphicsViewEvents.h"
#include "components/other/reImplementations/QGraphicsSceneEvents.h"

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
            directories::fileSelect = QDir("/system-onboard");
        } else if(ereaderVars::nickelApp == true) {
            qDebug() << "App is a Nickel app";
            directories::config = QDir("/mnt/onboard/.adds/sanki");
            directories::fileSelect = QDir("/mnt/onboard");
        } else {
            // Debug
            qWarning() << "App is in debug mode. If you are running on Nickel, you most propably forgot to install Nickel Menu, Kfmon and Koreader installed ( from the one click package )";
            directories::config = QDir("/sanki_debug_dir");
            directories::fileSelect = QDir("/");
        }
        directories::deckStorage = directories::config.path() + QDir::separator() + "decks";
        directories::sessionSaves = directories::config.path() + QDir::separator() + "sessions";
        directories::globalSettings.setFileName(directories::config.filePath("sanki.ini"));
    }

    qDebug() << "Main config path is" << directories::config;
    createDir(directories::config.absolutePath());
    qDebug() << "Deck storage path is" << directories::deckStorage;
    createDir(directories::deckStorage.absolutePath());
    qDebug() << "Session saves path is" << directories::sessionSaves;
    createDir(directories::sessionSaves.absolutePath());

#ifdef EREADER
    if(ereaderVars::inkboxUserApp) {
        QThread * audioThread = new QThread();
        audiothread * audioObject = new audiothread();
        audioObject->moveToThread(audioThread);
        QObject::connect(audioThread, &QThread::started, audioObject, &audiothread::start);
        audioThread->start();
    }
#endif


    QSettings settingsGlobal(directories::globalSettings.fileName(), QSettings::IniFormat);
    grender = settingsGlobal.value("renderLayer").toBool();
    qDebug() << "Render layer according to settings:" << grender;

    if(qgetenv("USE_NATIVE_RENDER") == "true") {
        qDebug() << "Disabling graphics render by env arg";
        grender = false;
    }

    disableFlashingEverywhere = settingsGlobal.value("disableFlashingEverywhere").toBool();
    qDebug() << "disableFlashingEverywhere according to settings:" << disableFlashingEverywhere;
    if(disableFlashingEverywhere == true) {
#ifdef EREADER
        KoboPlatformFunctions::setFlashing(false);
        flashing = false;
#endif
    }

    MainWindow w;

// Here were some weird issues with it crashing because of if else? so i used defines
#ifdef EREADER
    w.setAnimated(false);
    w.setFixedSize(ereaderVars::screenX, ereaderVars::screenY);

        warningsEnabled = true;

    // if i add here any if statement about including QGraphicsScene, it crashes... thats why below its so weird and splitted - yes it wastes memory, whatever

    // This is awesome
    // https://www.mobileread.com/forums/showthread.php?t=356673
    // Video 2 is the one using this
    // It uses QGraphicsView MinimalViewportUpdate to adjust it even more for eink render;
    // It has some issues:
    // Mainwindow cannot be added to a layout anymore, it refuses: Just use qwidget
    // QDialogs aren't using this render, they cause even more flashing by using full screen flashing?
    // Actually maybe? when dialogs have a parent in this mode, they have a window frame with an X button. Idk i cant delete it
    // Sometimes *** Error in `/sanki': double free or corruption (out): 0x7ebebbf0 *** appears? idk if im closing it right
    qGraphicsSceneEvents scene;
    if(grender == true) {
        qDebug() << "Applying graphics layer for ereader";
        scene.addWidget(&w);
    } else {
        qDebug() << "Not using graphics layer for ereader";
    }

    qGraphicsViewEvents customView;

    customView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    customView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if(grender == true) {
        customView.setBaseSize(ereaderVars::screenX, ereaderVars::screenY);
        customView.setFixedSize(ereaderVars::screenX, ereaderVars::screenY);
        customView.setMinimumSize(ereaderVars::screenX, ereaderVars::screenY);

        customView.setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
        customView.setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
        customView.setCacheMode(QGraphicsView::CacheNone);
        customView.setScene(&scene);

        // Madness to get gestures to work ;/
        // Children don't receive them, so i need to send them manually anyway
        //customView.setTabletTracking(true);
        //customView.viewport()->setTabletTracking(true);
        customView.viewport()->grabGesture(Qt::TapAndHoldGesture);
        customView.viewport()->grabGesture(Qt::PinchGesture);
        customView.viewport()->grabGesture(Qt::TapGesture);
        customView.grabGesture(Qt::TapAndHoldGesture);
        customView.grabGesture(Qt::PinchGesture);
        customView.grabGesture(Qt::TapGesture);
        QTapAndHoldGesture::setTimeout(2250);

        //customView.setAttribute(Qt::WA_AcceptTouchEvents);
        //customView.viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
        //w.setAttribute(Qt::WA_AcceptTouchEvents);
        QObject::connect(&customView, &qGraphicsViewEvents::eventSignal, &w, &MainWindow::gestureSlot);
        QObject::connect(&scene, &qGraphicsSceneEvents::eventSignal, &w, &MainWindow::gestureSlot);
    }

    if(grender == true) {
        graphic = &customView;
        customView.showFullScreen(); // VERY important for gestures - it needs to be full screen
    } else {
        w.showFullScreen();
    }
#else
    grender = false;
    w.show();
#endif

    a.exec();

    qDebug() << "App exited... Goodbye";
    exit(0);
}
