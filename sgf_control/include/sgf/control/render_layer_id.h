#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct RenderLayerTag {
        static std::string TypeName;
    };
    using RenderLayerId = ResourceId<RenderLayerTag>;
}
