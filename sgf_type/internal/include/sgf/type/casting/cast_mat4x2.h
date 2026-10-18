#pragma once

#include <glm/mat4x2.hpp>

#include "sgf/type/mat4x2.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat4x2> {
        using type = sgf::type::Mat4x2;
    };
    
    template <>
    struct GLMType<sgf::type::Mat4x2> {
        using type = glm::mat4x2;
    };
}
