#pragma once

#include <glm/mat2x3.hpp>
#include "sgf/type/mat2x3.h"

namespace sgf {
    Mat2x3 & toSgf(glm::mat2x3 & value);
    const Mat2x3 & toSgf(const glm::mat2x3 & value);
    
    glm::mat2x3 & toGlm(Mat2x3 & value);
    const glm::mat2x3 & toGlm(const Mat2x3 & value);
}
