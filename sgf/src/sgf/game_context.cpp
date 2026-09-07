#include "../../include/sgf/game_context.h"
#include <sgf/control/game_runtime.h>
#include "sgf/context/internal_render.h"

namespace sgf {
    GameContext::GameContext(const Contexts & contexts, const sgf::Camera & camera):
        contexts(contexts),
        gameRuntime(std::make_unique<sgf_core::GameRuntime>(
            this->contexts.get<sgf_core::PlatformContext>(),
            InternalRender(this->contexts.get<sgf::Render>()).RenderContext()
        )),
        ui(this->contexts),
        time(this->gameRuntime->Time()),
        camera(camera)
    {
        ui.setSize({
            (float)contexts.get<sgf_core::PlatformContext>().Window().getWidth(),
            (float)contexts.get<sgf_core::PlatformContext>().Window().getHeight()
        });
    }

    bool GameContext::isStop() const {
        return gameRuntime->isStop();
    }

    sgf::Render & GameContext::Render() {
        return contexts.get<sgf::Render>();
    }
    
    const sgf::Render & GameContext::Render() const {
        return contexts.get<sgf::Render>();
    }
    
    sgf::Camera & GameContext::Camera() {
        return camera;
    }
    
    const sgf::Camera & GameContext::Camera() const {
        return camera;
    }
    
    sgf::Time & GameContext::Time() {
        return time;
    }

    const sgf::Time & GameContext::Time() const {
        return time;
    }

    sgf::UI & GameContext::UI() {
        return ui;
    }

    const sgf::UI & GameContext::UI() const {
        return ui;
    }

    void GameContext::beginFrame() {
        ((sgf_core::FrameControl *)gameRuntime.get())->beginFrame();
    }

    void GameContext::endFrame() {
        ((sgf_core::FrameControl *)gameRuntime.get())->endFrame();
    }

    void GameContext::stop() {
        gameRuntime->stop();
    }
}
