#include "../../include/sgf/time.h"
#include <sgf/control/game_time.h>

namespace sgf {
    Time::Time(sgf_core::GameTime & gameTime):
        gameTime(gameTime)
    {
    }

    Time::TimeStamp Time::getCurrentTime() const {
        return std::chrono::time_point_cast<Duration>(gameTime.currentTime());
    }

    float Time::getDeltaTime() const {
        return gameTime.getDeltaTime();
    }
};
