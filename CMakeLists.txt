cmake_minimum_required(VERSION 3.16)

project(june VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Xml REQUIRED)
find_package(Qt6 COMPONENTS WebSockets REQUIRED)

qt_standard_project_setup()

add_subdirectory(core)
add_subdirectory(tagsystem)
add_subdirectory(influxdb)

add_subdirectory(server)
