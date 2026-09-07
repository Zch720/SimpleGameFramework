#pragma once

#include <memory>
#include "./contexts.h"
#include "./game_context.h"
#include "./game_loop_context.h"

#include <sgf/platform/platform_context.h> // delete

namespace sgf_core {
    class PlatformContext;
    class RenderContext;
}

namespace sgf_font {
    class FontRenderContext;
}

namespace sgf {
    class Game {
    public:
        struct WindowConfig {
            int width;
            int height;
            const std::string & title;
        };

        // using Contexts = sgf::Contexts<
        //     Render,
        //     sgf_core::PlatformContext
        // >;

    private:
        std::unique_ptr<sgf_core::PlatformContext> platformContext;
        std::unique_ptr<sgf_core::RenderContext> renderContext;
        std::unique_ptr<sgf_font::FontRenderContext> fontRenderContext;

        std::unique_ptr<Render> render;

        std::unique_ptr<sgf::GameContext> gameContext;
        std::unique_ptr<sgf::GameLoopContext> gameLoopContext;

        // Contexts contexts;

    public:
        Game(const WindowConfig & windowConfig);
        ~Game();

        sgf::GameContext & GameContext();
        sgf::GameLoopContext & GameLoopContext();

        sgf_core::PlatformContext & PlatformContext(); // delete 
    };
}
