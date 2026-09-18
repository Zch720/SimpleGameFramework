include_guard(GLOBAL)

function(sgf_require_stb)
    if (TARGET stb)
        return()
    endif()

    include(FetchContent)

    FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG f1c79c02822848a9bed4315b12c8c8f3761e1296
        SOURCE_SUBDIR "MADE-UP-DIRECTORY"
    )
    FetchContent_MakeAvailable(stb)
endfunction()
