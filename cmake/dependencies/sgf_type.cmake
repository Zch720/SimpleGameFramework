include_guard(GLOBAL)

function(sgf_require_sgf_type)
    if (TARGET sgf_type)
        return()
    endif()

    add_subdirectory(
        ${SGF_SOURCE_DIR}/sgf_type
        ${CMAKE_BINARY_DIR}/sgf_type
        EXCLUDE_FROM_ALL
    )
endfunction()
