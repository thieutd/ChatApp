#################################################################################################
## File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! ##
#################################################################################################

include($$(QxOrm_DIR)/QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_MODEL_VIEW_CLIENTMODELS
INCLUDEPATH += $$(QxOrm_DIR)/include
DESTDIR = $$PWD/bin/

LIBS += -L"$$(QxOrm_DIR)/lib"
LIBS += -L"$$PWD/../models/bin"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
LIBS += -l"ClientModelsd"
} else {
LIBS += -l"QxOrm"
LIBS += -l"ClientModels"
} # CONFIG(debug, debug|release)

CONFIG(debug, debug|release) {
TARGET = ClientModelsModeld
} else {
TARGET = ClientModelsModel
} # CONFIG(debug, debug|release)

include($$PWD/ClientModels.model_view.gen.pri)

!contains(DEFINES, _QX_UNITY_BUILD) {
SOURCES += $$PWD/src/ClientModels_main.model_view.gen.cpp
} # !contains(DEFINES, _QX_UNITY_BUILD)
