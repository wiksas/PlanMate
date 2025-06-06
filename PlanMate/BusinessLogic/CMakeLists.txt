cmake_minimum_required(VERSION 3.16)

project(BusinessLogic LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(LIB_SOURCES
  businesslogic.cpp
  businesslogic.h
  task.h
  task.cpp
  taskmanager.h
  taskmanager.cpp
  taskmodel.h
  taskmodel.cpp
)


add_library(BusinessLogic SHARED
  ${LIB_SOURCES}
  BusinessLogic_global.h
)


target_link_libraries(BusinessLogic PRIVATE Qt${QT_VERSION_MAJOR}::Core)


target_compile_definitions(BusinessLogic PRIVATE BUSINESSLOGIC_LIBRARY)


target_include_directories(BusinessLogic PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/BusinessLogic>
)
