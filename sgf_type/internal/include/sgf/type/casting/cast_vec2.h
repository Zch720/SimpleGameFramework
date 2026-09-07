#pragma once

#include <glm/vec2.hpp>
#include "sgf/type/vec2.h"

namespace sgf {
    Vec2 & toSgf(glm::vec2 & value);
    const Vec2 & toSgf(const glm::vec2 & value);
    
    glm::vec2 & toGlm(Vec2 & value);
    const glm::vec2 & toGlm(const Vec2 & value);
}
