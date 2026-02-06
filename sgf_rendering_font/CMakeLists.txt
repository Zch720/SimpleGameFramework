cmake_minimum_required(VERSION 3.14)
project(sgf_rendering_font)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_RENDERING_FONT_TESTS "Build sgf_rendering_font tests" OFF)

include(FetchContent)

if (SGF_RENDERING_FONT_TESTS)
    # get googletest package
    if(CMAKE_VERSION VERSION_LESS 3.24)
        FetchContent_Declare(googletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        )
    else()
        FetchContent_Declare(googletest
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

    # add sgf_control package
    find_package(sgf_control CONFIG QUIET)
    if (NOT TARGET sgf_control)
        message(STATUS "sgf_control target not found, adding as subdirectory")
        add_subdirectory(
            ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_control
            ${CMAKE_BINARY_DIR}/bin/sgf_control
            EXCLUDE_FROM_ALL
        )
    endif()
endif()

# get FreeType package
FetchContent_Declare(freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG 526ec5c47b9ebccc4754c85ac0c0cdf7c85a5e9b
)
set(SKIP_INSTALL_ALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(freetype)

# add sgf_rendering package
find_package(sgf_rendering_unsafe CONFIG QUIET)
if (NOT TARGET sgf_rendering_unsafe)
    message(STATUS "sgf_rendering_unsafe target not found, adding as subdirectory")
    add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_rendering
        ${CMAKE_BINARY_DIR}/bin/sgf_rendering
        EXCLUDE_FROM_ALL
    )
endif()

# add sgf_utils package
find_package(sgf_utils CONFIG QUIET)
if (NOT TARGET sgf_utils)
    message(STATUS "sgf_utils target not found, adding as subdirectory")
    add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_utils
        ${CMAKE_BINARY_DIR}/bin/sgf_utils
        EXCLUDE_FROM_ALL
    )
endif()

# create sgf_rendering_font library
file(GLOB_RECURSE sgf_rendering_font_sources src/*.cpp)

add_library(sgf_rendering_font ${sgf_rendering_font_sources})
target_include_directories(sgf_rendering_font
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sgf_rendering_font
    PUBLIC
        sgf_rendering
        sgf_utils
    PRIVATE
        sgf_rendering_unsafe
        freetype
)
target_compile_definitions(sgf_rendering_font
    PRIVATE
        PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
        RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"   
)


if (SGF_RENDERING_FONT_TESTS)
    # create unit test executable
    add_executable(sgf_rendering_font_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_rendering_font_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_rendering_font_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_rendering_font_test
        GTest::gtest_main
        sgf_rendering_font
        sgf_control
        sgf_rendering_unsafe
    )

    target_compile_definitions(sgf_rendering_font_test
        PRIVATE
            SGF_LOG
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_rendering_font_test)
endif()
