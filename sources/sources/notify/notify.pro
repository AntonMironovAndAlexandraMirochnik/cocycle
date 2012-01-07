QT       -= gui

TARGET = notify
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    notification.cpp \
    domain.cpp

HEADERS += \
    notify_global.h \
    notify.h \
    notification.h \
    domain.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

DEFINES += "nullptr=0"

OTHER_FILES += \
    index.html
