#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T18:12:07
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INDIE_LAUNCHER_VERSION = 0.2.0

win32:DEFINES   += TARGET_WINDOWS
unix:DEFINES    += TARGET_UNIX
macos:DEFINES   += TARGET_MACOS

TARGET = Epitech-Games-Launcher
TEMPLATE = app

RC_FILE = Launcher.rc

COMMON_PATH = $$PWD/../Common

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS "VERSION=$$INDIE_LAUNCHER_VERSION"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = $$COMMON_PATH

SOURCES += \
    main.cpp \
    launchermainwindows.cpp \
    gameitem.cpp \
    mastergetter.cpp \
    listgameitem.cpp \
    hashchecker.cpp \
    singletons.cpp \
    resoucesdownloader.cpp \
    cache.cpp \
    version.cpp \
    about.cpp \
    gamelauncher.cpp \
    $$COMMON_PATH/Json/src/Parser.cpp \
    $$COMMON_PATH/Json/src/Entity.cpp

HEADERS += \
    launchermainwindows.h \
    gameitem.h \
    mastergetter.h \
    listgameitem.h \
    hashchecker.h \
    singletons.h \
    resoucesdownloader.h \
    cache.h \
    version.h \
    about.h \
    gamelauncher.h \
    $$COMMON_PATH/Json/includes/Parser.hpp \
    $$COMMON_PATH/Json/includes/Entity.hpp

FORMS += \
        launchermainwindows.ui \
    gameitem.ui \
    about.ui

RESOURCES += \
    resources.qrc
