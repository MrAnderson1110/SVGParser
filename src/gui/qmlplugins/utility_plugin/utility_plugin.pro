#------------------------------------------------------------------------------#

ROOT_DIR  # путь к корневой директории проекта
SRC_DIR   # путь к исходным текстам
CORE_DIR  # путь к подмодулю/поддиректории core

THIS_DIR = $${PWD}
RESULT = $$find(THIS_DIR, src)
count(RESULT, 1) {
    ROOT_DIR = $${PWD}/../../../../
    SRC_DIR = $${ROOT_DIR}/src
    CORE_DIR = $${SRC_DIR}/gui
} else {
    ROOT_DIR = $${PWD}/../..
    SRC_DIR = $${ROOT_DIR}
    CORE_DIR = $${SRC_DIR}
}

LIBS_DIR = $${ROOT_DIR}/libs            # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins      # путь к собранным плагинам

#------------------------------------------------------------------------------#

TEMPLATE = lib
TARGET = utility_plugin
QT += qml quick
CONFIG += plugin

include(utility_plugin.pri)

LIBS += -L$${LIBS_DIR}/ -lutility
INCLUDEPATH += $${SRC_DIR}/utility

DESTDIR = $${PLUGINS_DIR}/$$TARGET
DEFINES += $${TARGET}_PLUGIN


for(var, $$list($$files(qmldir, true))) {
    LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
    ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
    ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$DESTDIR,)
    ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
    qmldir.files = ABSOLUTE_SOURCE_FILE
    qmldir.path = ABSOLUTE_DEST
    INSTALLS += qmldir
    mkpath($$ABSOLUTE_DEST)
    isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
    QMAKE_POST_LINK += \
    $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
}
for(var, $$list($$files($$quote(*.qml), true))) {
    LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
    ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
    ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$DESTDIR,)
    ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
    qmlfiles.files = ABSOLUTE_SOURCE_FILE
    qmlfiles.path = ABSOLUTE_DEST
    INSTALLS += qmlfiles
    mkpath($$ABSOLUTE_DEST)
    isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
    QMAKE_POST_LINK += \
    $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
}

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${PRO_NAME}/
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${PRO_NAME}/
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${PRO_NAME}/
