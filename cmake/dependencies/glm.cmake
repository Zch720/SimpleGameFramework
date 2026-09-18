include_guard(GLOBAL)

function(sgf_require_glm)
    if (TARGET glm::glm)
        return()
    endif()

    include(FetchContent)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 8d1fd52e5ab5590e2c81768ace50c72bae28f2ed
    )
    FetchContent_MakeAvailable(glm)
endfunction()
