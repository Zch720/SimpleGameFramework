#pragma once

#include <glm/mat2x2.hpp>

#include "sgf/type/mat2.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat2> {
        using type = sgf::type::Mat2;
    };
    
    template <>
    struct GLMType<sgf::type::Mat2> {
        using type = glm::mat2;
    };
}
