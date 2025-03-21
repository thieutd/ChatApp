cmake_minimum_required(VERSION 3.16)

project(ChatClient VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools Network StateMachine Concurrent Sql WebSockets)

set(TS_FILES resources/ChatClient_vi_VN.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

file(GLOB SOURCE_FILES "src/*.cpp" "src/restclients/*.cpp" "src/widgets/*.cpp")
file(GLOB HEADER_FILES "include/*.h" "include/restclients/*.h" "include/widgets/*.h")
qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${TS_FILES}
    resources/resources.qrc
)

file(GLOB UI_FILES "ui/*.ui")
qt_add_ui(${PROJECT_NAME} SOURCES ${UI_FILES})

add_subdirectory(config)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/configured_files/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Network Qt6::StateMachine Qt6::Concurrent Qt6::Sql Qt6::WebSockets)

include("$ENV{QxOrm_DIR}/QxOrm.cmake")
add_subdirectory(models)
add_subdirectory(modelview)
target_compile_definitions(QxOrm PRIVATE _QX_NO_TRACE_DLL_ATTACH_DETACH)
target_compile_definitions(ClientModels PRIVATE _QX_NO_TRACE_DLL_ATTACH_DETACH)
target_compile_definitions(ClientModelView PRIVATE _QX_NO_TRACE_DLL_ATTACH_DETACH)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/models/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/modelview/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${QX_LIBRARIES} QxOrm ClientModels ClientModelView)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(${PROJECT_NAME})
