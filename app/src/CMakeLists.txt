cmake_minimum_required(VERSION 3.17)

#project(utext VERSION 1.0 LANGUAGES CXX)

set(SOURCES mainwindow.cpp
        rope.cpp
        rope_node.cpp
        rope_tests.cpp
        tabmenager.cpp
        file_manager.cpp
        tabwelcome.cpp
        loggingcategories.cpp
        )

set(HEADERS mainwindow.h
        rope.h
        rope_node.h
        test_runner.h
        rope_tests.h
        tabmenager.h
        file_manager.h
        tabwelcome.h
        loggingcategories.h
        )

set(UI mainwindow.ui)

add_library(src ${SOURCES} ${HEADERS} ${UI})

target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Multimedia
)
