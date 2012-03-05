include(../GenericPrefix.pri)

QT -= gui
QT += network

LIBRARIES +=../Log

TARGET = Network
TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

include(../GenericPostfix.pri)

HEADERS += \
    Private/NetworkConstants.h \
    Private/NetworkConnectionClient.h \
    Private/NetworkConnectionServer.h \
    Private/NetworkController.h \
    Public/NetworkServer.h \
    Public/NetworkClient.h \
    Public/NetworkThread.h \
    Network.h

SOURCES += \
    Private/NetworkConnectionClient.cpp \
    Private/NetworkConnectionServer.cpp \
    Private/NetworkController.cpp \
    Public/NetworkServer.cpp \
    Public/NetworkClient.cpp \
    Public/NetworkThread.cpp
