#pragma once

#include <glm/vec4.hpp>

#include "sgf/type/vec4.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::vec4> {
        using type = sgf::type::Vec4;
    };
    
    template <>
    struct GLMType<sgf::type::Vec4> {
        using type = glm::vec4;
    };
}
