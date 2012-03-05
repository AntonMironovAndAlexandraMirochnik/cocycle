

win32 {
    LIBPREFIX = lib
    LIBSUFFIX = .a

    CONFIG(debug, debug|release) {
        LIBDIR = debug
    } else {
        LIBDIR = release
    }
}

message("----")
!isEmpty(LIBRARIES) {
    for(libpath, LIBRARIES) {
        libbase = $$basename(libpath)
        INCLUDEPATH += $$libpath
        LIBS += -L$${libpath}/$${LIBDIR}
        LIBS += -l$$libbase
        PRE_TARGETDEPS += $${libpath}/$${LIBDIR}/$${LIBPREFIX}$${libbase}$${LIBSUFFIX}
    }
    message($$INCLUDEPATH)
    message($$LIBS)
    message($$PRE_TARGETDEPS)
}
