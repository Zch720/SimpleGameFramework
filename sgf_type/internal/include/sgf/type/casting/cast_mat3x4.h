#pragma once

#include <glm/mat3x4.hpp>

#include "sgf/type/mat3x4.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat3x4> {
        using type = sgf::type::Mat3x4;
    };
    
    template <>
    struct GLMType<sgf::type::Mat3x4> {
        using type = glm::mat3x4;
    };
}
