#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct UpdateTag {
        static std::string TypeName;
    };
    using UpdateId = ResourceId<UpdateTag>;
    
    struct RenderTag {
        static std::string TypeName;
    };
    using RenderId = ResourceId<RenderTag>;
}
