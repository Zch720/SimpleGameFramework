#pragma once

#include <glm/mat4x4.hpp>

#include "sgf/type/mat4.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::mat4> {
        using type = sgf::type::Mat4;
    };
    
    template <>
    struct GLMType<sgf::type::Mat4> {
        using type = glm::mat4;
    };
}
