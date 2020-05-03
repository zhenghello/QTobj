#-------------------------------------------------
#
# Project created by QtCreator 2020-02-17T16:32:20
#
#-------------------------------------------------


TARGET = dog
TEMPLATE = lib

DEFINES += DOG_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dog.cpp \
    bilDog.cpp

HEADERS += \
        dog.h \
    bilDog.h \
    ianimal_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    libIAnimal.a




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lIAnimal
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lIAnimald

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./libIAnimal.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./libIAnimald.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./IAnimal.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./IAnimald.lib
