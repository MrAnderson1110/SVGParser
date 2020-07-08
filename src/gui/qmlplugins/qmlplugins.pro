
#------------------------------------------------------------------------------#

ROOT_DIR  # путь к корневой директории проекта
SRC_DIR   # путь к исходным текстам
CORE_DIR  # путь к подмодулю/поддиректории core

THIS_DIR = $${PWD}
RESULT = $$find(THIS_DIR, src)
count(RESULT, 1) {
    ROOT_DIR = $${PWD}/../../..
    SRC_DIR = $${ROOT_DIR}/src
    CORE_DIR = $${SRC_DIR}/gui
} else {
    ROOT_DIR = $${PWD}/../
    SRC_DIR = $${ROOT_DIR}
    CORE_DIR = $${SRC_DIR}
}

3RDPARTY_DIR =  $${SRC_DIR}/3rdparty    # путь к исходным текстам 3rdparty
LIBS_DIR = $${ROOT_DIR}/libs            # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins      # путь к собранным плагинам

#------------------------------------------------------------------------------#

TEMPLATE = subdirs

SUBDIRS += \
    parser \
    utility_plugin
