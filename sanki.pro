QT += \
    core \
    gui \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++11 \

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card_true_false.cpp \
    deck.cpp \
    deckplay.cpp \
    decks_scroll_bar.cpp \
    edit_deck.cpp \
    globals.cpp \
    main.cpp \
    mainwindow.cpp \
    mode_chooser.cpp \
    show_card.cpp \
    status_bar.cpp

HEADERS += \
    card_true_false.h \
    deck.h \
    deckplay.h \
    decks_scroll_bar.h \
    edit_deck.h \
    globals.h \
    mainwindow.h \
    mode_chooser.h \
    show_card.h \
    status_bar.h

FORMS += \
    card_true_false.ui \
    deck.ui \
    deckplay.ui \
    decks_scroll_bar.ui \
    edit_deck.ui \
    mainwindow.ui \
    mode_chooser.ui \
    show_card.ui \
    status_bar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources/sanki.qrc

#unix:!macx: LIBS += -L$$PWD/libs/zip/build/ -lzip
#INCLUDEPATH += $$PWD/libs/zip
#DEPENDPATH += $$PWD/libs/zip

INCLUDEPATH += libraries/karchive/src/include

#LIBS += -L"libraries/karchive/build/lib/" -lkarchive
