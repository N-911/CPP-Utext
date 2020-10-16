cmake_minimum_required(VERSION 3.15)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(./src/)
include_directories(../cmake-build-debug/app/src/src_autogen/include/ui_mainwindow.h)

add_compile_options(
        -std=c++17
#        -Wdev
#         -Werror
         -Wall
         -Wextra
         -Wpedantic
#        -Wno-unused-parameter
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui Multimedia MultimediaWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui Multimedia MultimediaWidgets REQUIRED)

#link_directories(../cmake-build-debug/)

add_subdirectory(src)

qt5_add_resources(RESOURCES resources/myresource.qrc)

add_executable(${CMAKE_PROJECT_NAME} main.cpp ${RESOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Multimedia
        src
)


