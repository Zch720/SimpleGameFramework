#pragma once

#include <sgf/utils/fwd.h>

namespace sgf_core {
    class GameRuntime;
    class GameTime;
    class FrameControl;

    struct UpdateTag;
    using UpdateId = ResourceId<UpdateTag>;
    class UpdatePipeline;
    
    struct RenderTag;
    using RenderId = ResourceId<RenderTag>;
    class RenderPipeline;

    struct RenderLayerTag;
    using RenderLayerId = ResourceId<RenderLayerTag>;
}
