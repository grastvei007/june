cmake_minimum_required(VERSION 3.16)

project(june VERSION 1.0.0 LANGUAGES CXX)

set(MIN_QT_VERSION 6.9)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6Core ${MIN_QT_VERSION} REQUIRED)
find_package(Qt6Widgets ${MIN_QT_VERSION} REQUIRED)
find_package(Qt6WebSockets ${MIN_QT_VERSION} REQUIRED)

qt_standard_project_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(core)
add_subdirectory(tagsystem)
add_subdirectory(influxdb)
add_subdirectory(device)
add_subdirectory(plugins)

add_subdirectory(server)
add_subdirectory(hwcom)
add_subdirectory(june)
add_subdirectory(tools)

add_dependencies(device tagsystem)
add_dependencies(hwcom device)
add_dependencies(juneserver tagsystem influxdb)
add_dependencies(june tagsystem)
