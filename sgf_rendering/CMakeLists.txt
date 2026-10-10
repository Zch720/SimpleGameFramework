cmake_minimum_required(VERSION 3.10)
project(sgf_rendering)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SGF_RENDERING_TESTS "Build sgf_rendering tests" OFF)

if (NOT DEFINED SGF_SOURCE_DIR)
    set(SGF_SOURCE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/..
        CACHE PATH "SGF source directory"
    )
endif()


# include dependencies
include(${SGF_SOURCE_DIR}/cmake/dependencies.cmake)

# third party dependencies
sgf_require_glad_sgf()
sgf_require_glm()
sgf_require_stb()

# sgf dependencies
sgf_require_sgf_type()
sgf_require_sgf_utils()


# create sgf_rendering library
file(GLOB_RECURSE sgf_rendering_sources ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(sgf_rendering ${sgf_rendering_sources})
target_include_directories(
    sgf_rendering
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${FETCHCONTENT_BASE_DIR}/stb-src
)
target_link_libraries(
    sgf_rendering
    PUBLIC
        glm::glm
        sgf_type
        sgf_utils
    PRIVATE
        glad_sgf
)

if (SGF_RENDERING_TESTS)
    sgf_require_gtest()
    sgf_require_glfw()

    add_executable(
        sgf_rendering_ut_test
        ${CMAKE_CURRENT_LIST_DIR}/test/unit_test/ut_all.cpp
    )
    set_target_properties(
        sgf_rendering_ut_test
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
            OUTPUT_NAME "ut_all"
    )
    target_compile_options(
        sgf_rendering_ut_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(
        sgf_rendering_ut_test
        PRIVATE
            GTest::gtest_main
            sgf_rendering
    )
    target_compile_definitions(
        sgf_rendering_ut_test
        PRIVATE
            PROJECT_DIR=${CMAKE_CURRENT_LIST_DIR}
            RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/resources
            TEST_RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/test/unit_test/resources
    )
    
    add_executable(
        sgf_rendering_it_test
        ${CMAKE_CURRENT_LIST_DIR}/test/integration_test/it_all.cpp
    )
    set_target_properties(
        sgf_rendering_it_test
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
            OUTPUT_NAME "it_all"
    )
    target_compile_options(
        sgf_rendering_it_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(
        sgf_rendering_it_test
        PRIVATE
            GTest::gtest_main
            glfw
            glad_sgf
            sgf_rendering
    )
    target_compile_definitions(
        sgf_rendering_it_test
        PRIVATE
            PROJECT_DIR=${CMAKE_CURRENT_LIST_DIR}
            RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/resources
            TEST_RESOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}/test/init_test/resources
    )
endif()
