#include "../../include/sgf/game.h"
#include <sgf/control/game_runtime.h>
#include <sgf/platform/platform_context.h>
#include <sgf/rendering/render_context.h>
#include <sgf/rendering/font/font_render_context.h>
#include <sgf/utils/exceptions/invalid_state.h>
#include <sgf/utils/logger/log.h>

namespace sgf {
    Game::Game(const WindowConfig & windowConfig) {
        platformContext = std::make_unique<sgf_core::PlatformContext>();
        platformContext->createWindow({
            .width = windowConfig.width,
            .height = windowConfig.height,
            .title = windowConfig.title
        });

        renderContext = std::make_unique<sgf_core::RenderContext>();
        renderContext->initialize();
        platformContext->setWindowClearBuffer(renderContext->getClearFrameBufferBits());

        fontRenderContext = std::make_unique<sgf_font::FontRenderContext>(*renderContext);

        render = std::make_unique<Render>(sgf::Contexts(*renderContext, *fontRenderContext));
    }

    Game::~Game() {
        renderContext->destroyAllResources();
        platformContext->terminate();
    }

    sgf::GameContext & Game::GameContext() {
        if (!gameContext) {
            if (gameLoopContext) {
                SGF_LOG_ERROR("Try to create a GameContext, but GameLoopContext already exist.");
                throw sgf_core::InvalidState("Try to create a GameContext, but GameLoopContext already exist.");
            } else {
                gameContext = std::unique_ptr<sgf::GameContext>(new sgf::GameContext({ *render, *platformContext }, Camera(renderContext->Camera())));
            }
        }
        return *gameContext;
    }

    sgf::GameLoopContext & Game::GameLoopContext() {
        if (!gameLoopContext) {
            if (gameContext) {
                SGF_LOG_ERROR("Try to create a GameLoopContext, but GameContext already exist.");
                throw sgf_core::InvalidState("Try to create a GameLoopContext, but GameContext already exist.");
            } else {
                gameLoopContext = std::unique_ptr<sgf::GameLoopContext>(new sgf::GameLoopContext({ *render, *platformContext }, Camera(renderContext->Camera())));
            }
        }
        return *gameLoopContext;
    }

    sgf_core::PlatformContext & Game::PlatformContext() {
        return *platformContext;
    }
}
