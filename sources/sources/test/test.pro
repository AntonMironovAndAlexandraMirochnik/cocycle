
SOURCES += \
    main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../notify/release/ -lnotify
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../notify/debug/ -lnotify
else:symbian: LIBS += -lnotify
else:unix: LIBS += -L$$OUT_PWD/../notify/ -lnotify

INCLUDEPATH += $$PWD/../notify
DEPENDPATH += $$PWD/../notify

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../notify/release/libnotify.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../notify/debug/libnotify.a
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../notify/libnotify.a
