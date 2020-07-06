
#--------------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..
SRC_DIR = $${ROOT_DIR}/src
LIBS_DIR = $${ROOT_DIR}/libs
PLUGINS_DIR = $${ROOT_DIR}/plugins

#--------------------------------------------------------------------------------------#

TEMPLATE = lib
DESTDIR = $LIBS_DIR
TARGET = svgparser
QT += core xml

include(svgparser.pri)

INCLUDEPATH += $${SRC_DIR}/svgparser

CONFIG(release, debug|release) {
    for(var, $$list($$files(qmldir, true))) {
        LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
        ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
        ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$QMLINSTALLDIR,)
        ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
        qmldir.files = ABSOLUTE_SOURCE_FILE
        qmldir.path = ABqmldirSOLUTE_DEST
        INSTALLS += qmldir
        mkpath($$ABSOLUTE_DEST)
        isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
        QMAKE_POST_LINK += \
        $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
    }
    for(var, $$list($$files($$quote(*.qml), true))) {
        LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
        ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
        ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$QMLINSTALLDIR,)
        ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
        qmlfiles.files = ABSOLUTE_SOURCE_FILE
        qmlfiles.path = ABSOLUTE_DEST
        INSTALLS += qmlfiles
        mkpath($$ABSOLUTE_DEST)
        isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
        QMAKE_POST_LINK += \
        $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
    }
    for(var, $$list($$files($$quote(*.png), true))) {
        LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
        ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
        ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$QMLINSTALLDIR,)
        ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
        qmlfiles.files = ABSOLUTE_SOURCE_FILE
        qmlfiles.path = ABSOLUTE_DEST
        INSTALLS += qmlfiles
        mkpath($$ABSOLUTE_DEST)
        isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
        QMAKE_POST_LINK += \
        $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
    }
    for(var, $$list($$files($$quote(*.js), true))) {
        LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
        ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
        ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$QMLINSTALLDIR,)
        ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
        qmlfiles.files = ABSOLUTE_SOURCE_FILE
        qmlfiles.path = ABSOLUTE_DEST
        INSTALLS += qmlfiles
        mkpath($$ABSOLUTE_DEST)
        isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
        QMAKE_POST_LINK += \
        $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
    }
}

unix:MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
unix:OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
unix:UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
