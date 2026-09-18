include_guard(GLOBAL)

function(sgf_require_sgf_rendering)
    if (TARGET sgf_rendering)
        return()
    endif()

    add_subdirectory(
        ${SGF_SOURCE_DIR}/sgf_rendering
        ${CMAKE_BINARY_DIR}/sgf_rendering
        EXCLUDE_FROM_ALL
    )
endfunction()
