#-------------------------------------------------
#
# Project created by QtCreator 2011-10-13T22:35:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2_client
TEMPLATE = app


SOURCES += main.cpp\
    algorythms.cpp \
        dialog.cpp \
        # myserver.cpp \
         # myclient.cpp

HEADERS  += dialog.h \
            # myserver.h \
            algorythms.h \
            myclient.h


FORMS    += dialog.ui

RESOURCES += \
    style.qrc



