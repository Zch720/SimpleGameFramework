#pragma once

#include <glm/mat2x4.hpp>

#include "sgf/type/mat2x4.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat2x4> {
        using type = sgf::type::Mat2x4;
    };
    
    template <>
    struct GLMType<sgf::type::Mat2x4> {
        using type = glm::mat2x4;
    };
}
