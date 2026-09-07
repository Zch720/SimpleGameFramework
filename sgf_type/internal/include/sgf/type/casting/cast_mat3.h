#pragma once

#include <glm/mat3x3.hpp>
#include "sgf/type/mat3.h"

namespace sgf {
    Mat3 & toSgf(glm::mat3 & value);
    const Mat3 & toSgf(const glm::mat3 & value);
    
    glm::mat3 & toGlm(Mat3 & value);
    const glm::mat3 & toGlm(const Mat3 & value);
}
