#include "main_menu/mainwindow.h"
#include "globals.h"

#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include <QLoggingCategory>

bool enableDebug = false;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(enableDebug == true) {
        QByteArray localMsg = msg.toLocal8Bit();
        const char *file = context.file ? context.file : "";
        const char *function = context.function ? context.function : "";
        switch (type) {
        case QtDebugMsg:
            if(context.line != 0) {
                fprintf(stderr, "Debug: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            } else {
                fprintf(stderr, "Debug: \"%s\"\n", localMsg.constData());
            }
            break;
        case QtInfoMsg:
            fprintf(stderr, "Info: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: \"%s\" (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
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

    if(qgetenv("CUSTOM_DEBUG_FORMAT") != "false") {
        qInstallMessageHandler(myMessageOutput);
    }

    qDebug() << "Sanki started";

    // Detect platform
#ifdef PC
    pc = true;
    qDebug() << "Detected platform PC";
#endif

#ifdef ereader
    ereader = true;
    qDebug() << "Detected platform ereader";
#endif

    QApplication a(argc, argv);
    MainWindow w;

    // TODO: deckSelect for ereader app-data and save the selected path to config, on pc too
    qDebug() << "deck storage path is" << directories::deckStorage;
    if(directories::deckStorage.exists() == false) {
        QDir newDir; // Why variable is needed
        newDir.mkpath(directories::deckStorage.path());
    }

    if(ereader) {
        // https://github.com/Szybet/niAudio/blob/main/apps-on-kobo/fix-special-characters-qt.md
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

        // TODO
        // Check and apply stylesheet if available
        /*
        screen_geometry();
        check_device();

        if(running_on_kobo == true)
        {
            // inkbox user app
            //QFile style_file("/mnt/onboard/.adds/inkbox/eink.qss");
            // TODO
            QFile style_file("/etc/eink.qss");

            if(style_file.exists() == false)
            {
                //debugLog("stylesheet file doesn't exist", "main.cpp", "main()");
            }

            style_file.open(QFile::ReadOnly);
            QString styleSheet = QLatin1String(style_file.readAll());
            a.setStyleSheet(styleSheet);
        }
        */
        w.showFullScreen();
    } else if(pc) {
        w.show();
    }

    return a.exec();
}
