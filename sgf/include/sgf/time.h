#pragma once

#include <chrono>

namespace sgf_core {
    class GameTime;
}

namespace sgf {
    class GameContext;
    class GameLoopContext;

    class Time {
    public:
        using Duration = std::chrono::duration<long, std::milli>;
        using TimeStamp = std::chrono::time_point<std::chrono::steady_clock, Duration>;

    private:
        friend GameContext;
        friend GameLoopContext;

        sgf_core::GameTime & gameTime;

        Time(sgf_core::GameTime & gameTime);

    public:
        TimeStamp getCurrentTime() const;
        float getDeltaTime() const;
    };
}
