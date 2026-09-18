include_guard(GLOBAL)

function(sgf_require_glad_sgf)
    if (TARGET glad_sgf)
        return()
    endif()

    include(FetchContent)

    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG 73db193f853e2ee079bf3ca8a64aa2eaf6459043
        SOURCE_SUBDIR cmake
    )
    FetchContent_MakeAvailable(glad)
    glad_add_library(
        glad_sgf
        STATIC
        REPRODUCIBLE
        LOADER
        API gl:compatibility=3.3
    )
endfunction()
