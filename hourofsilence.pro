QT       += core gui multimedia widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sounditem.cpp

HEADERS += \
    mainwindow.h \
    sounditem.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    defaultsounds/amongus-scream(LOUD).mp3 \
    defaultsounds/fnaf-hallway.mp3 \
    defaultsounds/minecraft-cave-ambience.mp3 \
    defaultsounds/reverb-fart.mp3 \
    defaultsounds/roblox-oof.mp3 \
    defaultsounds/squeaky-toy.mp3 \
    defaultsounds/stereo-knock.mp3 \
    defaultsounds/vine-boom.mp3 \
    defaultsounds/vine-omg(LOUD).mp3 \
    defaultsounds/what-the-dog-doin.mp3 \
    libs/libgcc_s_seh-1.dll \
    libs/libstdc++-6.dll \
    libs/libwinpthread.dll \
    libs/Qt5Core.dll \
    libs/Qt5Gui.dll \
    libs/Qt5Multimedia.dll \
    libs/Qt5Network.dll \
    libs/Qt5Widgets.dll \
    libs/platforms/qwindows.dll \
    readme.txt

DEPENDPATH = $${TARGET}/libs

target.path = $${TARGET}
libs.path = $${TARGET}
sounds.path = $${TARGET}/sounds
readme.path = $${TARGET}

sounds.files = defaultsounds/*
libs.files = libs/*
readme.files = readme.txt

INSTALLS+= target sounds libs readme
