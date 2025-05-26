cmake_minimum_required(VERSION 3.16)

project(PlanMate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


add_subdirectory(BusinessLogic)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(PlanMate
    ${PROJECT_SOURCES}
)

target_link_libraries(PlanMate
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        BusinessLogic
)
target_link_libraries(BusinessLogic
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)



target_include_directories(PlanMate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
