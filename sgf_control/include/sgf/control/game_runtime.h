#pragma once

#include <sgf/platform/platform_context.h>
#include <sgf/rendering/render_context.h>
#include "./frame_control.h"
#include "./game_time.h"

namespace sgf_core {
    class GameRuntime: public FrameControl {
    private:
        bool stopFlag;

        PlatformContext & platformContext;
        RenderContext & renderContext;

        GameTime gameTime;

        void beginFrame() override;
        void endFrame() override;

    public:
        GameRuntime(PlatformContext & platformContext, RenderContext & renderContext);

        bool isStop() const;

        GameTime & Time();
        const GameTime & Time() const;

        void stop();
    };
}
