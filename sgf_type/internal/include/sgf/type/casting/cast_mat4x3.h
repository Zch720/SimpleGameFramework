#pragma once

#include <glm/mat4x3.hpp>

#include "sgf/type/mat4x3.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat4x3> {
        using type = sgf::type::Mat4x3;
    };
    
    template <>
    struct GLMType<sgf::type::Mat4x3> {
        using type = glm::mat4x3;
    };
}
