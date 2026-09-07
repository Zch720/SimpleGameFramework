#pragma once

#include <glm/mat4x4.hpp>
#include "sgf/type/mat4.h"

namespace sgf {
    Mat4 & toSgf(glm::mat4 & value);
    const Mat4 & toSgf(const glm::mat4 & value);
    
    glm::mat4 & toGlm(Mat4 & value);
    const glm::mat4 & toGlm(const Mat4 & value);
}
