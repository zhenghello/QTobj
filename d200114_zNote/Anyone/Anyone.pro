#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = zNote
TEMPLATE = app

RC_ICONS = happy.ico   # Í¼±ê


# head file path
INCLUDEPATH +=  ./zLib/fdebug/ \
                ./zLib/strListTurn/


SOURCES += main.cpp\
            anyone.cpp \
            zLib/fdebug/fdebug.cpp \
            zLib/strListTurn/strlist2dat.cpp \
            zLib/strListTurn/strlist2tableWidget.cpp \
            zLib/strListTurn/dat2tableWidget.cpp


HEADERS  += anyone.h \
            zLib/fdebug/fdebug.h \
            zLib/strListTurn/strlist2dat.h \
            zLib/strListTurn/strlist2tableWidget.h \
            zLib/strListTurn/dat2tableWidget.h


FORMS    += anyone.ui \
            zLib/fdebug/fdebug.ui

RESOURCES += \
            anyone.qrc


