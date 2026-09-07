#pragma once

#include <glm/vec3.hpp>
#include "sgf/type/vec3.h"

namespace sgf {
    Vec3 & toSgf(glm::vec3 & value);
    const Vec3 & toSgf(const glm::vec3 & value);
    
    glm::vec3 & toGlm(Vec3 & value);
    const glm::vec3 & toGlm(const Vec3 & value);
}
