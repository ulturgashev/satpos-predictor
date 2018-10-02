SET(TESTED_TARGET prediction-qt)
SET(TARGET TestPrediction-Qt)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-exceptions -Wall -Wextra -pedantic")

FIND_PACKAGE(Qt5Core)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src/prediction
    ${CMAKE_SOURCE_DIR}/src/prediction-qt
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    AglStreamTest
    AglStreamTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    AlmanachsTest
    AlmanachsTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    CoordinateTest
    CoordinateTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    PrecisionDateTimeTest
    PrecisionDateTimeTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    PredictorTest
    PredictorTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    Point3Test
    Point3Test.cpp
    ${TESTED_TARGET}
)
