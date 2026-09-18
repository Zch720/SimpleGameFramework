include_guard(GLOBAL)

function(sgf_require_fmt)
    if (TARGET fmt)
        return()
    endif()

    include(FetchContent)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 407c905e45ad75fc29bf0f9bb7c5c2fd3475976f
    )
    FetchContent_MakeAvailable(fmt)
endfunction()
