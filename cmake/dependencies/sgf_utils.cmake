include_guard(GLOBAL)

function(sgf_require_sgf_utils)
    if (TARGET sgf_utils)
        return()
    endif()

    add_subdirectory(
        ${SGF_SOURCE_DIR}/sgf_utils
        ${CMAKE_BINARY_DIR}/sgf_utils
        EXCLUDE_FROM_ALL
    )
endfunction()
