
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../extended_cache/release/ -lextended_cache
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../extended_cache/debug/ -lextended_cache
else:symbian: LIBS += -lextended_cache
else:unix: LIBS += -L$$OUT_PWD/../../extended_cache/ -lextended_cache

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extended_cache/release/ -lextended_cache
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extended_cache/debug/ -lextended_cache
else:symbian: LIBS += -lextended_cache
else:unix: LIBS += -L$$OUT_PWD/../extended_cache/ -lextended_cache

INCLUDEPATH += $$PWD/../extended_cache
DEPENDPATH += $$PWD/../extended_cache

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extended_cache/release/libextended_cache.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extended_cache/debug/libextended_cache.a
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../extended_cache/libextended_cache.a
