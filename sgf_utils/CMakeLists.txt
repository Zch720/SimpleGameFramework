cmake_minimum_required(VERSION 3.24)
project(sgf_utils)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SGF_UTILS_TESTS "Build sgf_utils tests" OFF)

if (NOT DEFINED SGF_SOURCE_DIR)
    set(SGF_SOURCE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/..
        CACHE PATH "SGF source directory"
    )
endif()


# include dependencies
include(${SGF_SOURCE_DIR}/cmake/dependencies.cmake)

# third party dependencies
sgf_require_fmt()
sgf_require_spdlog()


# create sgf_utils library
file(GLOB_RECURSE sgf_utils_sources ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(sgf_utils ${sgf_utils_sources})
target_include_directories(
    sgf_utils
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(
    sgf_utils
    PUBLIC
        fmt::fmt
    PRIVATE
        spdlog::spdlog
)

if (SGF_UTILS_TESTS)
    sgf_require_gtest()

    add_executable(
        sgf_utils_ut_test
        ${CMAKE_CURRENT_LIST_DIR}/test/unit_test/ut_all.cpp
    )
    set_target_properties(
        sgf_utils_ut_test
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
            OUTPUT_NAME "ut_all"
    )
    target_compile_options(
        sgf_utils_ut_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(
        sgf_utils_ut_test
        PRIVATE
            GTest::gtest_main
            sgf_utils
    )
    target_compile_definitions(
        sgf_utils_ut_test
        PRIVATE
            PROJECT_DIR=${CMAKE_CURRENT_LIST_DIR}
            RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/resources
            TEST_RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/test/unit_test/resources
    )
endif()
