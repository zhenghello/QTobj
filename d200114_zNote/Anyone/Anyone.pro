#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T21:12:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = zNote
TEMPLATE = app
OBJECTS_DIR  = tmp
MOC_DIR      = tmp

RC_ICONS = happy.ico   # ico


# head file path
INCLUDEPATH +=  ./zLib/fdebug/ \
                ./zLib/strListTurn/ \
                ./zLib/fTableFast/ \

SOURCES += main.cpp\
            anyone.cpp \
            zLib/fdebug/fdebug.cpp \
            zLib/strListTurn/strlist2dat.cpp \
            zLib/strListTurn/strlist2tableWidget.cpp \
            zLib/strListTurn/dat2tableWidget.cpp \
            zLib/fTableFast/ftablefast.cpp


HEADERS  += anyone.h \
            zLib/fdebug/fdebug.h \
            zLib/strListTurn/strlist2dat.h \
            zLib/strListTurn/strlist2tableWidget.h \
            zLib/strListTurn/dat2tableWidget.h \
            zLib/fTableFast/ftablefast.h \



FORMS    += anyone.ui \
            zLib/fdebug/fdebug.ui

RESOURCES += \
            anyone.qrc


