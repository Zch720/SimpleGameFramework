#pragma once

#include <glm/vec2.hpp>

#include "sgf/type/vec2.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::vec2> {
        using type = sgf::type::Vec2;
    };
    
    template <>
    struct GLMType<sgf::type::Vec2> {
        using type = glm::vec2;
    };
}
