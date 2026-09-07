#include "sgf/type/casting/cast_mat2x4.h"

namespace sgf {
    Mat2x4 & toSgf(glm::mat2x4 & value) {
        static_assert(sizeof(Mat2x4) == sizeof(glm::mat2x4));
        return reinterpret_cast<Mat2x4 &>(value);
    }

    const Mat2x4 & toSgf(const glm::mat2x4 & value) {
        static_assert(sizeof(Mat2x4) == sizeof(glm::mat2x4));
        return reinterpret_cast<const Mat2x4 &>(value);
    }
    
    glm::mat2x4 & toGlm(Mat2x4 & value) {
        static_assert(sizeof(Mat2x4) == sizeof(glm::mat2x4));
        return reinterpret_cast<glm::mat2x4 &>(value);
    }

    const glm::mat2x4 & toGlm(const Mat2x4 & value) {
        static_assert(sizeof(Mat2x4) == sizeof(glm::mat2x4));
        return reinterpret_cast<const glm::mat2x4 &>(value);
    }
}
