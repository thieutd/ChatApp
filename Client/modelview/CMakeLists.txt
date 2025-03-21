#################################################################################################
## File created by QxEntityEditor 1.2.8 (2025/03/13 03:57) : please, do NOT modify this file ! ##
#################################################################################################

cmake_minimum_required(VERSION 3.1)

project(ClientModelView LANGUAGES CXX)

if(NOT TARGET QxOrm)
   add_subdirectory("$ENV{QxOrm_DIR}/" ./QxOrm)
endif() # NOT TARGET QxOrm
if(NOT TARGET ClientModels)
   add_subdirectory("../models/" ./ClientModels)
endif() # NOT TARGET ClientModels

include("$ENV{QxOrm_DIR}/QxOrm.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(CLIENTMODELS_MODEL_HEADERS
    ./include/ClientModels_precompiled_header.model_view.gen.h
    ./include/ClientModels_export.model_view.gen.h
    ./include/Message.model_view.gen.h
    ./include/Room.model_view.gen.h
    ./include/RoomMembership.model_view.gen.h
    ./include/User.model_view.gen.h
    ./custom/include/Message.model_view.h
    ./custom/include/Room.model_view.h
    ./custom/include/RoomMembership.model_view.h
    ./custom/include/User.model_view.h
   )

if(_QX_UNITY_BUILD)

   set(CLIENTMODELS_MODEL_SRCS ./src/ClientModels_all.model_view.gen.cpp)

else() # _QX_UNITY_BUILD

   set(CLIENTMODELS_MODEL_SRCS
       ./src/Message.model_view.gen.cpp
       ./src/Room.model_view.gen.cpp
       ./src/RoomMembership.model_view.gen.cpp
       ./src/User.model_view.gen.cpp
       ./custom/src/Message.model_view.cpp
       ./custom/src/Room.model_view.cpp
       ./custom/src/RoomMembership.model_view.cpp
       ./custom/src/User.model_view.cpp
       ./src/ClientModels_main.model_view.gen.cpp
      )

endif() # _QX_UNITY_BUILD

add_library(ClientModelView SHARED ${CLIENTMODELS_MODEL_SRCS} ${CLIENTMODELS_MODEL_HEADERS})

target_compile_definitions(ClientModelView PRIVATE -D_BUILDING_MODEL_VIEW_CLIENTMODELS )

if(COMMAND target_precompile_headers)
   target_precompile_headers(ClientModelView PRIVATE ./include/ClientModels_precompiled_header.model_view.gen.h)
endif() # (COMMAND target_precompile_headers)

target_link_libraries(ClientModelView ${QX_LIBRARIES} QxOrm ClientModels )

set_target_properties(ClientModelView PROPERTIES
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

qx_auto_source_group("${CLIENTMODELS_MODEL_SRCS};${CLIENTMODELS_MODEL_HEADERS}")
