
#--------------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/..
SRC_DIR = $${ROOT_DIR}/src
LIBS_DIR = $${ROOT_DIR}/libs
PLUGINS_DIR = $${ROOT_DIR}/plugins

#--------------------------------------------------------------------------------------#

TEMPLATE = subdirs
CONFIG -= debug_and_release_target

SUBDIRS += $$SRC_DIR/app \
           $$SRC_DIR/gui \
           $$SRC_DIR/svgparser \

QML_IMPORT_PATH += $${SRC_DIR} $${PLUGINS_DIR}
