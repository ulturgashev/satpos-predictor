CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

IF(POLICY CMP0043)
    CMAKE_POLICY(SET CMP0043 OLD)
ENDIF()

PROJECT(PredictionApplication)

ADD_DEFINITIONS(-DAPPLICATION_NAME="${PROJECT_NAME}")

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-exceptions -Wall -Wextra -pedantic")

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Gui)

SET(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/AlmanachModel.cpp
    src/ApplicationSettings.cpp
    src/PredictionModel.cpp
    src/CoordinateWidget.cpp
)

SET(FORMS
    src/CoordinateWidget.ui
    src/MainWindow.ui
)

QT5_WRAP_UI(UI_HEADERS ${FORMS})

ADD_EXECUTABLE(
    ${PROJECT_NAME}
    ${SOURCES}
    ${UI_HEADERS}
)

TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    prediction-qt
    Qt5::Core
    Qt5::Widgets
)
