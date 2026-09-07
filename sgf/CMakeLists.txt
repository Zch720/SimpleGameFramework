cmake_minimum_required(VERSION 3.14)
project(sgf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_TESTS "Build SGF tests" OFF)

include(FetchContent)

if (SGF_TESTS)
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

# get sgf_rendering, sgf_platform, sgf_audio, sgf_control, sgf_rendering_font, sgf_type
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_rendering
    ${CMAKE_BINARY_DIR}/bin/sgf_rendering
    EXCLUDE_FROM_ALL
)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_platform
    ${CMAKE_BINARY_DIR}/bin/sgf_platform
    EXCLUDE_FROM_ALL
)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_audio
    ${CMAKE_BINARY_DIR}/bin/sgf_audio
    EXCLUDE_FROM_ALL
)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_control
    ${CMAKE_BINARY_DIR}/bin/sgf_control
    EXCLUDE_FROM_ALL
)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_rendering_font
    ${CMAKE_BINARY_DIR}/bin/sgf_rendering_font
    EXCLUDE_FROM_ALL
)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_type
    ${CMAKE_BINARY_DIR}/bin/sgf_type
    EXCLUDE_FROM_ALL
)

file(GLOB_RECURSE sgf_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/src/*.cpp
)

add_library(sgf ${sgf_sources})
target_include_directories(sgf
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/include
)
target_link_libraries(sgf
    PUBLIC
        sgf_utils
        sgf_type
    PRIVATE
        sgf_platform
        sgf_rendering
        sgf_rendering_font
        sgf_audio
        sgf_control
        sgf_type_internal
)

if (SGF_TESTS)
    # create unit test executable
    add_executable(
        sgf_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_test
        GTest::gtest_main
        sgf
        sgf_rendering
        sgf_platform
        sgf_audio
        sgf_control
        sgf_rendering_font
    )
    target_compile_definitions(sgf_test
        PRIVATE
            SGF_LOG
            SGF_DEBUG_LOG
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_test)
endif()