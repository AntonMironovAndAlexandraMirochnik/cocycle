include(../GenericPrefix.pri)

LIBRARIES +=../Network
LIBRARIES +=../Serializers
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
    Login/LoginDialogController.h \
    Login/LoginWidget.h \
    MainWindow/MainWindowController.h \
    MainWindow/MainWindow.h

SOURCES += \
    Main.cpp \
    Application.cpp \
    MainController/MainController.cpp \
    Login/LoginDialogController.cpp \
    Login/LoginWidget.cpp \
    MainWindow/MainWindowController.cpp \
    MainWindow/MainWindow.cpp

FORMS += \
    Login/LoginWidget.ui \
    MainWindow/MainWindow.ui

RESOURCES += \
    Resources.qrc

include(../GenericPostfix.pri)
