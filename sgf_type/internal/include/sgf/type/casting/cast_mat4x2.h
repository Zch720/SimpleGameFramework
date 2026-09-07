#pragma once

#include <glm/mat4x2.hpp>
#include "sgf/type/mat4x2.h"

namespace sgf {
    Mat4x2 & toSgf(glm::mat4x2 & value);
    const Mat4x2 & toSgf(const glm::mat4x2 & value);
    
    glm::mat4x2 & toGlm(Mat4x2 & value);
    const glm::mat4x2 & toGlm(const Mat4x2 & value);
}
