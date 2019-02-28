# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = gui

TEMPLATE = app
TARGET = HePICS

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

HEADERS += \
    welcomewindow.h \
    mainwindow.h \
    platform_mode_section.h \
    imagesection.h \
    controlsection.h \
    Assistant.h \
    Classifier.h \
    controlsection.h \
    Convolutional_layer.h \
    Convolutional_LayerFPGA.h \
    DataSaver.h \
    Exception.h \
    Fully_connected_layer.h \
    Function_layer.h \
    Image.h \
    imagesection.h \
    Layer.h \
    mainwindow.h \
    Maxpool_layer.h \
    Network.h \
    Parser.h \
    platform_mode_section.h \
    Result.h \
    Scheduler.h \
    welcomewindow.h

SOURCES += \
    welcomewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    platform_mode_section.cpp \
    imagesection.cpp \
    controlsection.cpp \
    Assistant.cpp \
    Classifier.cpp \
    controlsection.cpp \
    Convolutional_layer.cpp \
    Convolutional_LayerFPGA.cpp \
    DataSaver.cpp \
    Exception.cpp \
    Fully_connected_layer.cpp \
    Function_layer.cpp \
    Hepics.cpp \
    Image.cpp \
    imagesection.cpp \
    Layer.cpp \
    main.cpp \
    mainwindow.cpp \
    Maxpool_layer.cpp \
    Network.cpp \
    Parser.cpp \
    platform_mode_section.cpp \
    Result.cpp \
    Scheduler.cpp \
    welcomewindow.cpp

HEADERS = \
   $$PWD/controlsection.h \
   $$PWD/imagesection.h \
   $$PWD/mainwindow.h \
   $$PWD/platform_mode_section.h \
   $$PWD/welcomewindow.h

SOURCES = \
   $$PWD/controlsection.cpp \
   $$PWD/imagesection.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp \
   $$PWD/platform_mode_section.cpp \
   $$PWD/welcomewindow.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

