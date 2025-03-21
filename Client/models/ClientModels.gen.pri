#################################################################################################
## File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! ##
#################################################################################################

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER += $$PWD/include/ClientModels_precompiled_header.gen.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

HEADERS += $$PWD/include/ClientModels_precompiled_header.gen.h
HEADERS += $$PWD/include/ClientModels_export.gen.h

HEADERS += $$PWD/include/Message.gen.h
HEADERS += $$PWD/include/Room.gen.h
HEADERS += $$PWD/include/RoomMembership.gen.h
HEADERS += $$PWD/include/User.gen.h

HEADERS += $$PWD/custom/include/Message.h
HEADERS += $$PWD/custom/include/Room.h
HEADERS += $$PWD/custom/include/RoomMembership.h
HEADERS += $$PWD/custom/include/User.h

HEADERS += $$PWD/include/RoomType.gen.h
HEADERS += $$PWD/include/UserRole.gen.h
HEADERS += $$PWD/include/RoomMembershipRole.gen.h

HEADERS += $$PWD/custom/include/RoomType.h
HEADERS += $$PWD/custom/include/UserRole.h
HEADERS += $$PWD/custom/include/RoomMembershipRole.h

contains(DEFINES, _QX_UNITY_BUILD) {

SOURCES += $$PWD/src/ClientModels_all.gen.cpp

} else {

SOURCES += $$PWD/src/Message.gen.cpp
SOURCES += $$PWD/src/Room.gen.cpp
SOURCES += $$PWD/src/RoomMembership.gen.cpp
SOURCES += $$PWD/src/User.gen.cpp

SOURCES += $$PWD/custom/src/Message.cpp
SOURCES += $$PWD/custom/src/Room.cpp
SOURCES += $$PWD/custom/src/RoomMembership.cpp
SOURCES += $$PWD/custom/src/User.cpp

SOURCES += $$PWD/src/RoomType.gen.cpp
SOURCES += $$PWD/src/UserRole.gen.cpp
SOURCES += $$PWD/src/RoomMembershipRole.gen.cpp

SOURCES += $$PWD/custom/src/RoomType.cpp
SOURCES += $$PWD/custom/src/UserRole.cpp
SOURCES += $$PWD/custom/src/RoomMembershipRole.cpp

} # contains(DEFINES, _QX_UNITY_BUILD)

include($$PWD/custom/ClientModels.pri)
