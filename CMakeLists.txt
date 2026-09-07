cmake_minimum_required(VERSION 3.14)
project(simple_game_framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# get sgf
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/sgf
    ${CMAKE_BINARY_DIR}/bin/sgf
    EXCLUDE_FROM_ALL
)

# file(GLOB_RECURSE sgf_sources src/*.cpp)

# add_library(game ${sgf_sources})
# target_include_directories(game
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/include
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/internal_include
# )
# target_link_libraries(game
#     PUBLIC
#         sgf
# )
