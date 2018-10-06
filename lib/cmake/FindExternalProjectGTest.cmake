INCLUDE(ExternalProject)

ExternalProject_Add(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.0
        TIMEOUT 10
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        CMAKE_ARGS -DBUILD_GTEST:BOOL=ON -DBUILD_GMOCK:BOOL=OFF
        BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/src/gtest-build/googletest/libgtest.a
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

ADD_LIBRARY(libgtest IMPORTED STATIC GLOBAL)
ADD_DEPENDENCIES(libgtest gtest)

ExternalProject_Get_Property(gtest source_dir binary_dir)

SET(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
SET(GMOCK_INCLUDE_DIRS ${source_dir}/googlemock/include)

SET_TARGET_PROPERTIES(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googletest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

SET(GTEST_LIBRARIES ${binary_dir}/googletest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
SET(GTEST_LIBRARY ${GTEST_LIBRARIES})
SET(GTEST_MAIN_LIBRARY ${binary_dir}/googletest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a)