#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T16:34:35
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test001
TEMPLATE = app


SOURCES += main.cpp\
        lcd.cpp \
    block.cpp \
    button.cpp

HEADERS  += lcd.h \
    button.h \
    block.h

FORMS    += lcd.ui

RESOURCES += lcd.qrc
DEPENDPATH += .
INCLUDEPATH += .

#OTHER_FILES += \
