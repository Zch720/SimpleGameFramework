#pragma once

namespace sgf_core {
    class FrameControl {
    public:
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
    };
}
