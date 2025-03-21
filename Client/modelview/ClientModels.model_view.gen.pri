#################################################################################################
## File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! ##
#################################################################################################

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER += $$PWD/include/ClientModels_precompiled_header.model_view.gen.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

HEADERS += $$PWD/include/ClientModels_precompiled_header.model_view.gen.h
HEADERS += $$PWD/include/ClientModels_export.model_view.gen.h

HEADERS += $$PWD/include/Message.model_view.gen.h
HEADERS += $$PWD/include/Room.model_view.gen.h
HEADERS += $$PWD/include/RoomMembership.model_view.gen.h
HEADERS += $$PWD/include/User.model_view.gen.h

HEADERS += $$PWD/custom/include/Message.model_view.h
HEADERS += $$PWD/custom/include/Room.model_view.h
HEADERS += $$PWD/custom/include/RoomMembership.model_view.h
HEADERS += $$PWD/custom/include/User.model_view.h

contains(DEFINES, _QX_UNITY_BUILD) {

SOURCES += $$PWD/src/ClientModels_all.model_view.gen.cpp

} else {

SOURCES += $$PWD/src/Message.model_view.gen.cpp
SOURCES += $$PWD/src/Room.model_view.gen.cpp
SOURCES += $$PWD/src/RoomMembership.model_view.gen.cpp
SOURCES += $$PWD/src/User.model_view.gen.cpp

SOURCES += $$PWD/custom/src/Message.model_view.cpp
SOURCES += $$PWD/custom/src/Room.model_view.cpp
SOURCES += $$PWD/custom/src/RoomMembership.model_view.cpp
SOURCES += $$PWD/custom/src/User.model_view.cpp

} # contains(DEFINES, _QX_UNITY_BUILD)

include($$PWD/custom/ClientModels.model_view.pri)
