#pragma once

#include <string_view>

namespace sgf::utils {
    class Resource {
    public:
        struct Construct;

        static std::string_view getTypeName();
    };
}
