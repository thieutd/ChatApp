#################################################################################################
## File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! ##
#################################################################################################

cmake_minimum_required(VERSION 3.1)

project(ClientModels LANGUAGES CXX)

if(NOT TARGET QxOrm)
   add_subdirectory("$ENV{QxOrm_DIR}/" ./QxOrm)
endif() # NOT TARGET QxOrm

include("$ENV{QxOrm_DIR}/QxOrm.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(CLIENTMODELS_HEADERS
    ./include/ClientModels_precompiled_header.gen.h
    ./include/ClientModels_export.gen.h
    ./include/Message.gen.h
    ./include/Room.gen.h
    ./include/RoomMembership.gen.h
    ./include/User.gen.h
    ./custom/include/Message.h
    ./custom/include/Room.h
    ./custom/include/RoomMembership.h
    ./custom/include/User.h
    ./include/RoomType.gen.h
    ./include/UserRole.gen.h
    ./include/RoomMembershipRole.gen.h
    ./custom/include/RoomType.h
    ./custom/include/UserRole.h
    ./custom/include/RoomMembershipRole.h
   )

if(_QX_UNITY_BUILD)

   set(CLIENTMODELS_SRCS ./src/ClientModels_all.gen.cpp)

else() # _QX_UNITY_BUILD

   set(CLIENTMODELS_SRCS
       ./src/Message.gen.cpp
       ./src/Room.gen.cpp
       ./src/RoomMembership.gen.cpp
       ./src/User.gen.cpp
       ./custom/src/Message.cpp
       ./custom/src/Room.cpp
       ./custom/src/RoomMembership.cpp
       ./custom/src/User.cpp
       ./src/RoomType.gen.cpp
       ./src/UserRole.gen.cpp
       ./src/RoomMembershipRole.gen.cpp
       ./custom/src/RoomType.cpp
       ./custom/src/UserRole.cpp
       ./custom/src/RoomMembershipRole.cpp
       ./src/ClientModels_main.gen.cpp
      )

endif() # _QX_UNITY_BUILD

add_library(ClientModels SHARED ${CLIENTMODELS_SRCS} ${CLIENTMODELS_HEADERS})

target_compile_definitions(ClientModels PRIVATE -D_BUILDING_CLIENTMODELS)

if(COMMAND target_precompile_headers)
   target_precompile_headers(ClientModels PRIVATE ./include/ClientModels_precompiled_header.gen.h)
endif() # (COMMAND target_precompile_headers)

target_link_libraries(ClientModels ${QX_LIBRARIES} QxOrm)

set_target_properties(ClientModels PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                     )

qx_auto_source_group("${CLIENTMODELS_SRCS};${CLIENTMODELS_HEADERS}")
