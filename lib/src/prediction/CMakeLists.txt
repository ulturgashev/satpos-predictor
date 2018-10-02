PROJECT(prediction)

ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fvisibility=hidden")

SET(HEADERS
	ephemerides.h
	converters.h
	geometric.h
)

SET(SOURCES
	ephemerides.c
	converters.c
	geometric.c
)

ADD_LIBRARY(
    ${PROJECT_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)
