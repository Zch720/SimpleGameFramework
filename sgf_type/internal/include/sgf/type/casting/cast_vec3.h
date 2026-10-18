#pragma once

#include <glm/vec3.hpp>

#include "sgf/type/vec3.h"
#include "sgf/type/casting/cast.h"

namespace sgf::type {
    template <>
    struct SGFType<glm::vec3> {
        using type = sgf::type::Vec3;
    };
    
    template <>
    struct GLMType<sgf::type::Vec3> {
        using type = glm::vec3;
    };
}
