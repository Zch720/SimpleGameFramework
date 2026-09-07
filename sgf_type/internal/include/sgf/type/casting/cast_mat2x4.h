#pragma once

#include <glm/mat2x4.hpp>
#include "sgf/type/mat2x4.h"

namespace sgf {
    Mat2x4 & toSgf(glm::mat2x4 & value);
    const Mat2x4 & toSgf(const glm::mat2x4 & value);
    
    glm::mat2x4 & toGlm(Mat2x4 & value);
    const glm::mat2x4 & toGlm(const Mat2x4 & value);
}
