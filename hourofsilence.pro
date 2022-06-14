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
    defaultsounds/amongus-scream.mp3 \
    defaultsounds/bruh.mp3 \
    defaultsounds/minecraft-old-oof.mp3 \
    defaultsounds/reverb-fart.mp3 \
    defaultsounds/roblox-oof.mp3 \
    defaultsounds/vine-boom.mp3 \
    defaultsounds/what-the-dog-doin.mp3

target.path = $${TARGET}/bin
libs.path = $${TARGET}/bin
sounds.path = $${TARGET}/sounds
sounds.files = defaultsounds/*
libs.files = libs/*

INSTALLS+= target sounds libs
