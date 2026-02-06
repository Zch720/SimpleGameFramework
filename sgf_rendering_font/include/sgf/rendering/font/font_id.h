#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_font {
    struct FontTag {
        static std::string TypeName;
    };
    using FontId = sgf_core::ResourceId<FontTag>;
}
