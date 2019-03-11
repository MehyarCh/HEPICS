TEMPLATE = app
TARGET = HePICS

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

HEADERS += \
    welcome_window.h \
    main_window.h \
    platform_mode_section.h \
    image_section.h \
    control_section.h

SOURCES += \
    welcome_window.cpp \
    main.cpp \
    main_window.cpp \
    platform_mode_section.cpp \
    image_section.cpp \
    control_section.cpp

