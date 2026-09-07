#include "../../../include/sgf/control/game_runtime.h"
#include <sgf/utils/exceptions/invalid_state.h>
#include <sgf/utils/logger/log.h>

namespace sgf_core {
    GameRuntime::GameRuntime(PlatformContext & platformContext, RenderContext & renderContext):
        stopFlag(false),
        platformContext(platformContext),
        renderContext(renderContext),
        gameTime(30, 500)
    {
    }

    bool GameRuntime::isStop() const {
        return stopFlag || platformContext.Window().isClose();
    }

    GameTime & GameRuntime::Time() {
        return gameTime;
    }

    const GameTime & GameRuntime::Time() const {
        return gameTime;
    }

    void GameRuntime::beginFrame() {
        platformContext.Runtime().onFrameBegin();
        gameTime.beginFrame();
    }

    void GameRuntime::endFrame() {
        gameTime.sleep();
        platformContext.Runtime().onFrameEnd();
    }

    void GameRuntime::stop() {
        stopFlag = true;
    }
}
