
#--------------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../../
SRC_DIR = $${ROOT_DIR}/src
LIBS_DIR = $${ROOT_DIR}/libs
PLUGINS_DIR = $${ROOT_DIR}/plugins

#--------------------------------------------------------------------------------------#

TEMPLATE = app
TARGET = creator
DESTDIR += $${ROOT_DIR}/app

include(creator.pri)
DEFINES += $${upper($$TARGET)}_LIB

QT += xml qml quick core gui widgets

INCLUDEPATH += $${SRC_DIR}/creator

LIBS += -L$${LIBS_DIR}/ -lsvgparser
INCLUDEPATH += $${SRC_DIR}/svgparser

LIBS += -L$${LIBS_DIR}/ -lgenerator
INCLUDEPATH += $${SRC_DIR}/generator

LIBS += -L$${LIBS_DIR}/ -lutility
INCLUDEPATH += $${SRC_DIR}/utility


MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
