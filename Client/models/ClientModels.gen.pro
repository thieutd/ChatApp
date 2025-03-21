#################################################################################################
## File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! ##
#################################################################################################

include($$(QxOrm_DIR)/QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_CLIENTMODELS
INCLUDEPATH += $$(QxOrm_DIR)/include
DESTDIR = $$PWD/bin/

CONFIG(debug, debug|release) {
TARGET = ClientModelsd
} else {
TARGET = ClientModels
} # CONFIG(debug, debug|release)

LIBS += -L"$$(QxOrm_DIR)/lib"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
} else {
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

include($$PWD/ClientModels.gen.pri)

!contains(DEFINES, _QX_UNITY_BUILD) {
SOURCES += $$PWD/src/ClientModels_main.gen.cpp
} # !contains(DEFINES, _QX_UNITY_BUILD)
