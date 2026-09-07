#pragma once

#include <glm/mat4x3.hpp>
#include "sgf/type/mat4x3.h"

namespace sgf {
    Mat4x3 & toSgf(glm::mat4x3 & value);
    const Mat4x3 & toSgf(const glm::mat4x3 & value);
    
    glm::mat4x3 & toGlm(Mat4x3 & value);
    const glm::mat4x3 & toGlm(const Mat4x3 & value);
}
