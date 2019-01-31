/*
 * HePICS.pro
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

TEMPLATE = app
TARGET = HePICS

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

HEADERS += \
    welcomewindow.h \
    mainwindow.h \
    platform_mode_section.h \
    imagesection.h \
    controlsection.h

SOURCES += \
    welcomewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    platform_mode_section.cpp \
    imagesection.cpp \
    controlsection.cpp

