QT       -= gui

TARGET = extended_cache
TEMPLATE = lib
CONFIG += staticlib

DEFINES += "nullptr=0"

SOURCES +=

HEADERS += extended_cache.h \
    extended_cache_delegate.h \
    extended_cache_global.h \
    extended_cache_impl.h \
    extended_cache_object.h \
    extended_cache_object_delegate.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    index.html
