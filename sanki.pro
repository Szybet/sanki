QT += \
    core \
    gui \
    sql \
    widgets \
    charts

CONFIG += \
    c++11 \
    c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Cleaning
SOURCES += \
    cardView/deckPlay.cpp \
    cardView/functions/helperFunctions.cpp \
    cardView/modeChooser.cpp \
    cardView/modes/boxes.cpp \
    cardView/modes/completlyRandom.cpp \
    cardView/modes/randomNoRepeat.cpp \
    components/files/file.cpp \
    components/files/fileChooser.cpp \
    components/other/askForText.cpp \
    components/other/griditemspacer.cpp \
    components/other/statistics.cpp \
    components/settings.cpp \
    components/statusBarC.cpp \
    global.cpp \
    mainMenu/decks/deck.cpp \
    components/other/keyboard.cpp \
    main.cpp \
    cardView/buttons/showCard.cpp \
    components/other/toast.cpp \
    mainMenu/editGridObject.cpp \
    mainMenu/fancyGrid.cpp \
    mainMenu/mainWindow.cpp \
    mainMenu/sessions/session.cpp \
    mainMenu/sessions/sessionStruct.cpp

HEADERS += \
    cardView/deckPlay.h \
    cardView/functions/helperFunctions.h \
    cardView/modeChooser.h \
    cardView/modes/boxes.h \
    cardView/modes/completlyRandom.h \
    cardView/modes/randomNoRepeat.h \
    components/files/file.h \
    components/files/fileChooser.h \
    components/other/askForText.h \
    components/other/griditemspacer.h \
    components/other/statistics.h \
    components/settings.h \
    components/statusBarC.h \
    global.h \
    mainMenu/decks/deck.h \
    components/other/keyboard.h \
    cardView/buttons/showCard.h \
    components/other/toast.h \
    mainMenu/editGridObject.h \
    mainMenu/fancyGrid.h \
    mainMenu/mainWindow.h \
    mainMenu/sessions/session.h \
    mainMenu/sessions/sessionStruct.h

FORMS += \
    cardView/deckPlay.ui \
    cardView/modeChooser.ui \
    components/files/file.ui \
    components/files/fileChooser.ui \
    components/other/askForText.ui \
    components/other/griditemspacer.ui \
    components/other/statistics.ui \
    components/settings.ui \
    components/statusBarC.ui \
    mainMenu/decks/deck.ui \
    components/other/keyboard.ui \
    cardView/buttons/showCard.ui \
    components/other/toast.ui \
    mainMenu/editGridObject.ui \
    mainMenu/fancyGrid.ui \
    mainMenu/mainWindow.ui \
    mainMenu/sessions/session.ui

# Default rules for deployment.
unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources/sanki.qrc

INCLUDEPATH += $$PWD/libraries/zip_libraries/zip/src/
DEPENDPATH += $$PWD/libraries/zip_libraries/zip/src/

TARGET_DEVICE = $$(TARGET_DEVICE) # You need to set TARGET_DEVICE in your qtcreator kits

# message(Target is: $$TARGET_DEVICE)
# https://stackoverflow.com/questions/39338987/how-to-detect-target-ios-architecture-in-qmake
# https://stackoverflow.com/questions/60898385/if-else-if-equivalent-for-qmake-pro-qt-file

if(contains(TARGET_DEVICE, KOBO)) {
    LIBS += -L$$PWD/libraries/zip_libraries/lib-build/KOBO -lzip
    DESTDIR = build/kobo/
    OBJECTS_DIR = build/kobo/.obj
    MOC_DIR = build/kobo/.moc
    RCC_DIR = build/kobo/.rcc
    UI_DIR = build/kobo/.ui
    message("Choosed libraries for KOBO")
    DEFINES += KOBO=true
}

if(contains(TARGET_DEVICE, PC)) {
    LIBS += -L$$PWD/libraries/zip_libraries/lib-build/PC -lzip
    DESTDIR = build/pc/
    OBJECTS_DIR = build/pc/.obj
    MOC_DIR = build/pc/.moc
    RCC_DIR = build/pc/.rcc
    UI_DIR = build/pc/.ui
    message("Choosed libraries for PC")
    DEFINES += PC=true
}

if(isEmpty(TARGET_DEVICE)) {
    error("No target specified for libraries")
}
