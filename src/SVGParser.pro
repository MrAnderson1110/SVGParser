
#--------------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../
SRC_DIR = $${ROOT_DIR}/src
LIBS_DIR = $${ROOT_DIR}/libs
PLUGINS_DIR = $${ROOT_DIR}/plugins

#--------------------------------------------------------------------------------------#

TEMPLATE = subdirs
CONFIG -= debug_and_release_target
CONFIG += ordered

SUBDIRS += $$SRC_DIR/utility \
           $$SRC_DIR/generator \
           $$SRC_DIR/svgparser \
           $$SRC_DIR/creator \
           $$SRC_DIR/gui

QML_IMPORT_PATH += $${SRC_DIR} $${PLUGINS_DIR}
