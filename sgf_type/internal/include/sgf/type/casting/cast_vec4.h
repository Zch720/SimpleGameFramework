#pragma once

#include <glm/vec4.hpp>
#include "sgf/type/vec4.h"

namespace sgf {
    Vec4 & toSgf(glm::vec4 & value);
    const Vec4 & toSgf(const glm::vec4 & value);
    
    glm::vec4 & toGlm(Vec4 & value);
    const glm::vec4 & toGlm(const Vec4 & value);
}
