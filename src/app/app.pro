
#--------------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..
SRC_DIR = $${ROOT_DIR}/src
LIBS_DIR = $${ROOT_DIR}/libs
PLUGINS_DIR = $${ROOT_DIR}/plugins

#--------------------------------------------------------------------------------------#

TEMPLATE = app
TARGET += app
DESTDIR += $${ROOT_DIR}/app

include(app.pri)

QT += xml qml quick core gui

INCLUDEPATH += $${SRC_DIR}/app

LIBS += -L$${LIBS_DIR}/ -lsvgparser
INCLUDEPATH += $${SRC_DIR}/svgparser

#Это понадобится, когда будет GUI
#LIBS += -L$${LIBS_DIR}/
#INCLUDEPATH += $${SRC_DIR}/gui/

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
