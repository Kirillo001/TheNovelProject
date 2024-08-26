QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backgroundwidget.cpp \
    chapterselection.cpp \
    characterwidget.cpp \
    gamesettings.cpp \
    loadmenu.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    musicmanager.cpp \
    novellagame.cpp \
    settingsmanager.cpp

HEADERS += \
    backgroundwidget.h \
    chapterselection.h \
    characterwidget.h \
    gamesettings.h \
    loadmenu.h \
    mainmenu.h \
    mainwindow.h \
    musicmanager.h \
    novellagame.h \
    settingsmanager.h

FORMS += \
    chapterselection.ui \
    gamesettings.ui \
    loadmenu.ui \
    mainmenu.ui \
    mainwindow.ui \
    novellagame.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
