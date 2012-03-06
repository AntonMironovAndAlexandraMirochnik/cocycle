include(../GenericPrefix.pri)

LIBRARIES +=../Network
LIBRARIES +=../Log

QT += network
QT += xml

TARGET = CocycleClient
TEMPLATE = app
CONFIG += staticlib
CONFIG += create_prl

HEADERS += \
    Application.h \
    MainController/MainController.h \
    Ui/MainWindowController.h \
    Ui/LoginDialogController.h

SOURCES += \
    Main.cpp \
    Application.cpp \
    MainController/MainController.cpp \
    Ui/MainWindowController.cpp \
    Ui/LoginDialogController.cpp

FORMS += \
    Ui/MainWindowController.ui \
    Ui/LoginDialogController.ui

include(../GenericPostfix.pri)


