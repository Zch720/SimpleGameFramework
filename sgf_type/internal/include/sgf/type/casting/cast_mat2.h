#pragma once

#include <glm/mat2x2.hpp>
#include "sgf/type/mat2.h"

namespace sgf {
    Mat2 & toSgf(glm::mat2 & value);
    const Mat2 & toSgf(const glm::mat2 & value);
    
    glm::mat2 & toGlm(Mat2 & value);
    const glm::mat2 & toGlm(const Mat2 & value);
}
