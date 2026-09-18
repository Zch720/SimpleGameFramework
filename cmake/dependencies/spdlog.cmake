include_guard(GLOBAL)

function(sgf_require_spdlog)
    if (TARGET spdlog)
        return()
    endif()

    include(FetchContent)

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG 486b55554f11c9cccc913e11a87085b2a91f706f
    )
    FetchContent_MakeAvailable(spdlog)
endfunction()
