#pragma once

namespace sgf {
    enum class FramePhase {
        BEGIN_FRAME,
        PRE_UPDATE,
        UPDATE,
        POST_UPDATE,
        PRE_RENDER,
        RENDER,
        POST_RENDER,
        END_FRAME
    };
}
