SET(TESTED_TARGET prediction)
SET(TARGET TestPredictionLibrary)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src/prediction
    ${CMAKE_SOURCE_DIR}/src/test
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    EphemeridesTest
    EphemeridesTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    GeometricTest
    GeometricTest.cpp
    ${TESTED_TARGET}
)

ADD_TARGET_TO_TEST(
    ${TARGET}
    ConverterTest
    ConverterTest.cpp
    ${TESTED_TARGET}
)
