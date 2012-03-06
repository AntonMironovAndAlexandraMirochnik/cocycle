include(../GenericPrefix.pri)

QT -= gui
QT += xml

TARGET = Serializers
TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

HEADERS += \
    DomDocument.h \
    VariantSerializer.h \
    VariantBackwardSerializer.h \
    Serializers.h

SOURCES += \
    DomDocument.cpp \
    VariantSerializer.cpp \
    VariantBackwardSerializer.cpp

include(../GenericPostfix.pri)
