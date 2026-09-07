#pragma once

#include <glm/mat3x4.hpp>
#include "sgf/type/mat3x4.h"

namespace sgf {
    Mat3x4 & toSgf(glm::mat3x4 & value);
    const Mat3x4 & toSgf(const glm::mat3x4 & value);
    
    glm::mat3x4 & toGlm(Mat3x4 & value);
    const glm::mat3x4 & toGlm(const Mat3x4 & value);
}
