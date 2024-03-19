cmake_minimum_required(VERSION 3.5)

project(SmartCalcV2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH "/home/dorthava/Qt/6.6.1/gcc_64")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ui/mainwindow.ui
    ui/smartcalcview.ui
    ui/creditview.ui
    ui/depositview.ui
    ui/graphview.ui

    deposit/deposit_date.h
    deposit/deposit_date.cc
    deposit/deposit_model.h
    deposit/deposit_model.cc
    deposit/deposit_controller.cc
    deposit/deposit_controller.h
    deposit/depositview.h
    deposit/depositview.cpp
    
    credit/creditview.cpp
    credit/creditview.h
    credit/credit_controller.cc
    credit/credit_controller.h
    credit/credit_model.cc
    credit/credit_model.h

    smartcalc/smartcalcview.cc
    smartcalc/smartcalcview.h
    smartcalc/smartcalc_controller.cc
    smartcalc/smartcalc_controller.h
    smartcalc/smartcalc_model.cc
    smartcalc/smartcalc_model.h
    smartcalc/token.cc
    smartcalc/token.h

    graph/graphview.cpp
    graph/graphview.h
    graph/graph_controller.cc
    graph/graph_controller.h
    graph/graph_model.cc
    graph/graph_model.h

    graph/qcustomplot.cpp
    graph/qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalcV2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalcV2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalcV2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalcV2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalcV2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SmartCalcV2)
endif()

target_link_libraries(SmartCalcV2 PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(SmartCalcV2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SmartCalcV2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalcV2)
endif()
