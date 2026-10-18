cmake_minimum_required(VERSION 3.10)
project(sgf_type)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SGF_TYPE_TESTS "Build sgf_type tests" OFF)

if (NOT DEFINED SGF_SOURCE_DIR)
    set(SGF_SOURCE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/..
        CACHE PATH "SGF source directory"
    )
endif()


# include dependencies
include(${SGF_SOURCE_DIR}/cmake/dependencies.cmake)

# third party dependencies
sgf_require_glm()


# create sgf_type library
file(GLOB_RECURSE sgf_type_sources ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(sgf_type ${sgf_type_sources})
target_include_directories(
    sgf_type
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# create sgf_type_internal library
# file(GLOB_RECURSE sgf_type_internal_sources ${CMAKE_CURRENT_LIST_DIR}/internal/src/*.cpp)

# add_library(sgf_type_internal ${sgf_type_internal_sources})
# target_include_directories(
#     sgf_type_internal
#     PUBLIC
#         ${CMAKE_CURRENT_LIST_DIR}/internal/include
# )
# target_link_libraries(
#     sgf_type_internal
#     PUBLIC
#         glm::glm
#         sgf_type
# )

add_library(sgf_type_internal INTERFACE)
target_include_directories(
    sgf_type_internal
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/internal/include
)
target_link_libraries(
    sgf_type_internal
    INTERFACE
        glm::glm
        sgf_type
)


if (SGF_TYPE_TESTS)
    sgf_require_gtest()

    add_executable(
        sgf_type_ut_test
        ${CMAKE_CURRENT_LIST_DIR}/test/unit_test/ut_all.cpp
    )
    set_target_properties(
        sgf_type_ut_test
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
            OUTPUT_NAME "ut_all"
    )
    target_compile_options(
        sgf_type_ut_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(
        sgf_type_ut_test
        PRIVATE
            GTest::gtest_main
            sgf_type
            sgf_type_internal
    )
    target_compile_definitions(
        sgf_type_ut_test
        PRIVATE
            PROJECT_DIR=${CMAKE_CURRENT_LIST_DIR}
            RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/resources
            TEST_RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/test/unit_test/resources
    )
endif()
