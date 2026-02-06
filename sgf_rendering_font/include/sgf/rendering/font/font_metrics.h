#pragma once

#include <cstdint>

namespace sgf_font {
    struct FontMetrics {
        int64_t ascent;
        int64_t descent;
        int64_t lineGap;
    };
}
