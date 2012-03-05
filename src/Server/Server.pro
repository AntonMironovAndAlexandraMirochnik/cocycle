include(../GenericPrefix.pri)

LIBRARIES +=../Network
LIBRARIES +=../Log

QT += network

TARGET = CocycleServer
TEMPLATE = app
CONFIG += staticlib
CONFIG += create_prl

HEADERS += \
    Ui/MainWindowController.h \
    MainController/MainController.h

SOURCES += \
    Main.cpp \
    Ui/MainWindowController.cpp \
    MainController/MainController.cpp

FORMS += \
    Ui/MainWindow.ui

include(../GenericPostfix.pri)

