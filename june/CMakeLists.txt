cmake_minimum_required(VERSION 3.16)
project(june)

set_target_properties(PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

link_directories(${CMAKE_BINARY_DIR}/$<CONFIG>/lib)


set(CMAKE_INCLUDE_CURRENT_DIR "YES")
set(CMAKE_AUTOMOC "YES")
set(CMAKE_AUTOUIC "YES")

find_package(Qt6 COMPONENTS WebSockets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(june
    main.cpp
    app.h
    app.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui

    gui/climateguiwidget.h
    gui/climateguiwidget.cpp
    gui/menubar.h
    gui/menubar.cpp
    gui/plugins.h
    gui/plugins.cpp
    gui/plugins.ui
    gui/statusbar.h
    gui/statusbar.cpp
    gui/tabletool.h
    gui/tabletool.cpp
    gui/triggerdatatablemodel.h
    gui/triggerdatatablemodel.cpp
    gui/triggerguiwidget.h
    gui/triggerguiwidget.cpp
    gui/pigpiowidget.h
    gui/pigpiowidget.cpp
    gui/pigpiotablemodel.h
    gui/pigpiotablemodel.cpp

    data/climatedata.h
    data/climatedata.cpp

    data/farmingdata.h
    data/farmingdata.cpp
    data/gardenadata.h
    data/gardenadata.cpp
    data/logvaluedata.h
    data/logvaluedata.cpp
    data/tagsocketbindingdata.h
    data/tagsocketbindingdata.cpp
    data/triggerdata.h
    data/triggerdata.cpp
    data/trigger.h
    data/trigger.cpp
    data/pigpiodata.h
    data/pigpiodata.cpp

    gui/centralwidgetfactory.h
    gui/addtrigger.h
    gui/addtrigger.cpp

    gui/addvaluedialog.h
    gui/addvaluedialog.cpp
    gui/farmingwidget.h
    gui/farmingwidget.cpp
    gui/gardenawidget.h
    gui/gardenawidget.cpp

    gui/logvaluetablemodel.h
    gui/logvaluetablemodel.cpp
    gui/logvaluewidget.h
    gui/logvaluewidget.cpp
    gui/comboboxdelegate.h
    gui/comboboxdelegate.cpp
    gui/tagsocketbindingwidget.h
    gui/tagsocketbindingwidget.cpp
    gui/tagsocketbindingtablemodel.h
    gui/tagsocketbindingtablemodel.cpp

    gui/addvaluedialog.ui
    gui/addtrigger.ui
    gui/farmingwidget.ui
    gui/gardenawidget.ui
)


target_link_libraries(june PRIVATE Qt6::WebSockets
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    Qt6::SerialPort)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode")
    target_link_libraries(june PRIVATE tagsystemd)
    target_link_libraries(june PRIVATE cored)
else()
    message("Release mode")
    target_link_libraries(june PRIVATE tagsystem)
    target_link_libraries(june PRIVATE core)
target_link_libraries(june PRIVATE Qt6::Core)
endif()


set_target_properties(june
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin
)


