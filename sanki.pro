QT += \
    core \
    gui \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++11 \
    c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Cleaning
SOURCES += \
    card_view/card_true_false.cpp \
    components/file.cpp \
    components/file_chooser.cpp \
    components/settings.cpp \
    main_menu/deck.cpp \
    card_view/deckplay.cpp \
    main_menu/decks_scroll_bar.cpp \
    main_menu/edit_deck.cpp \
    components/keyboard.cpp \
    main.cpp \
    main_menu/mainwindow.cpp \
    card_view/mode_chooser.cpp \
    card_view/show_card.cpp \
    components/status_bar.cpp \
    components/toast.cpp

HEADERS += \
    card_view/card_true_false.h \
    components/file.h \
    components/file_chooser.h \
    components/settings.h \
    main_menu/deck.h \
    card_view/deckplay.h \
    main_menu/decks_scroll_bar.h \
    main_menu/edit_deck.h \
    globals.h \
    components/keyboard.h \
    main_menu/mainwindow.h \
    card_view/mode_chooser.h \
    card_view/show_card.h \
    components/status_bar.h \
    components/toast.h

FORMS += \
    card_view/card_true_false.ui \
    components/file.ui \
    components/file_chooser.ui \
    components/settings.ui \
    main_menu/deck.ui \
    card_view/deckplay.ui \
    main_menu/decks_scroll_bar.ui \
    main_menu/edit_deck.ui \
    components/keyboard.ui \
    main_menu/mainwindow.ui \
    card_view/mode_chooser.ui \
    card_view/show_card.ui \
    components/status_bar.ui \
    components/toast.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources/sanki.qrc

INCLUDEPATH += $$PWD/libraries/zip_libraries/zip/src/
DEPENDPATH += $$PWD/libraries/zip_libraries/zip/src/

IOS_ARCH = $$(IOS_ARCH)
!isEmpty(IOS_ARCH): TARGET_ARCH = $$IOS_ARCH
message(Target arch is: $$TARGET_ARCH)
# https://stackoverflow.com/questions/39338987/how-to-detect-target-ios-architecture-in-qmake
# https://stackoverflow.com/questions/60898385/if-else-if-equivalent-for-qmake-pro-qt-file

contains(TARGET_ARCH, Kobo) {
    LIBS += -L$$PWD/libraries/zip_libraries/lib-build/KOBO -lzip
    message(Library for kobo)
} else {
    LIBS += -L$$PWD/libraries/zip_libraries/lib-build/PC -lzip
    message(Library for pc)
}
