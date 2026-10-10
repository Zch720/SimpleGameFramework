#pragma once

#include <variant>

namespace sgf::rendering {
    using UniformType = std::variant<
        int,
        float
    >;

    class Uniform {
    public:
        void setProvider();
    };
}
