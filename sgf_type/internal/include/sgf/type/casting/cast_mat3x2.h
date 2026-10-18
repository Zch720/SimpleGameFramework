#pragma once

#include <glm/mat3x2.hpp>

#include "sgf/type/mat3x2.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat3x2> {
        using type = sgf::type::Mat3x2;
    };
    
    template <>
    struct GLMType<sgf::type::Mat3x2> {
        using type = glm::mat3x2;
    };
}
