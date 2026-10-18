#pragma once

#include <glm/mat3x3.hpp>

#include "sgf/type/mat3.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat3> {
        using type = sgf::type::Mat3;
    };
    
    template <>
    struct GLMType<sgf::type::Mat3> {
        using type = glm::mat3;
    };
}
