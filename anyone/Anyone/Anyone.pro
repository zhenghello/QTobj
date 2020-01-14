#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Anyone
TEMPLATE = app

RC_ICONS = happy.ico   # Í¼±ê


# head file path
INCLUDEPATH += ./zLib/fdebug/

SOURCES += main.cpp\
        anyone.cpp \
    ./zLib/fdebug/fdebug.cpp

HEADERS  += anyone.h \
    ./zLib/fdebug/fdebug.h

FORMS    += anyone.ui \
    ./zLib/fdebug/fdebug.ui

RESOURCES += \
    anyone.qrc


