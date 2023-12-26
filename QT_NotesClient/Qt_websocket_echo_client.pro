QT       += core gui network websockets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    notewidget.cpp \
    Note.cpp \
    JsonParser.cpp \
    tests/tests/test_mainwindow.cpp \
    tests/tests/test_notewidget.cpp


HEADERS += \
    mainwindow.h \
    notewidget.h \
    Note.h \
    JsonParser.h \
    nlohmann/json.hpp \
    tests/tests/test_mainwindow.h \
    tests/tests/test_notewidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc
