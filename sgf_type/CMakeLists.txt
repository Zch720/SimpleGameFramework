cmake_minimum_required(VERSION 3.14)
project(sgf_type)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_TYPE_TESTS "Build sgd_type tests" OFF)

include(FetchContent)

if (SGF_TYPE_TESTS)
    # get googletest package
    if(CMAKE_VERSION VERSION_LESS 3.24)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        )
    else()
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
            DOWNLOAD_EXTRACT_TIMESTAMP 1
        )
    endif()

    if(NOT UNIX)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    set(BUILD_GMOCK OFF)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
endif()

# get glm package
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 8d1fd52e5ab5590e2c81768ace50c72bae28f2ed
)
FetchContent_MakeAvailable(glm)

# create sgf_type library
file(GLOB_RECURSE sgf_type_sources src/*.cpp)

add_library(sgf_type ${sgf_type_sources})
target_include_directories(sgf_type
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB_RECURSE sgf_type_internal_sources internal/src/*.cpp)

add_library(sgf_type_internal ${sgf_type_internal_sources})
target_include_directories(sgf_type_internal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/include
)
target_link_libraries(sgf_type_internal
    PUBLIC
        sgf_type
        glm
)

if (SGF_TYPE_TESTS)
    # create unit test executable
    add_executable(
        sgf_type_unit_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_type_unit_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_type_unit_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_type_unit_test
        GTest::gtest_main
        sgf_type
        sgf_type_internal
    )
    target_compile_definitions(sgf_type_unit_test
        PRIVATE
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_type_unit_test)
endif()
