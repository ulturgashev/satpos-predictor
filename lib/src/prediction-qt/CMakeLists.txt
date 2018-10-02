PROJECT(prediction-qt)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-exceptions -Wall -Wextra -pedantic")

FIND_PACKAGE(Qt5 REQUIRED Core)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/src/prediction)

SET(HEADERS
    AglStream.h
    Almanach.h
    CartesianCoordinate.h
    GeodeticCoordinate.h
    Point3.h
    Predictor.h
    Prediction.h
    PrecisionDateTime.h
    SphericalCoordinate.h
)

SET(SOURCES
    AglStream.cpp
    Almanach.cpp
    CartesianCoordinate.cpp
    GeodeticCoordinate.cpp
    Point3.cpp
    Predictor.cpp
    Prediction.cpp
    PrecisionDateTime.cpp
    SphericalCoordinate.cpp
)

ADD_LIBRARY(
    ${PROJECT_NAME}
    SHARED
    ${HEADERS}
    ${SOURCES}
)

TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    prediction
    Qt5::Core
)

TARGET_INCLUDE_DIRECTORIES(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
