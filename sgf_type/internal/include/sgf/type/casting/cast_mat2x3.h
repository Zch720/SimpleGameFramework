#pragma once

#include <glm/mat2x3.hpp>

#include "sgf/type/mat2x3.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat2x3> {
        using type = sgf::type::Mat2x3;
    };
    
    template <>
    struct GLMType<sgf::type::Mat2x3> {
        using type = glm::mat2x3;
    };
}
