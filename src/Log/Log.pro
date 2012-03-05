include(../GenericPrefix.pri)

QT -= gui

TARGET = Log
TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

HEADERS += \
    Log.h \
    LogConstants.h \
    LogMessage.h \
    LogEvent.h \
    LogController.h \
    LogCStyle.h \
    LogFileController.h

SOURCES += \
    LogMessage.cpp \
    LogEvent.cpp \
    LogController.cpp \
    LogCStyle.cpp \
    LogFileController.cpp

include(../GenericPostfix.pri)
