#pragma once

#include <glm/mat3x2.hpp>
#include "sgf/type/mat3x2.h"

namespace sgf {
    Mat3x2 & toSgf(glm::mat3x2 & value);
    const Mat3x2 & toSgf(const glm::mat3x2 & value);
    
    glm::mat3x2 & toGlm(Mat3x2 & value);
    const glm::mat3x2 & toGlm(const Mat3x2 & value);
}
