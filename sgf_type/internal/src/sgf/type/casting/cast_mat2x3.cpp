#include "sgf/type/casting/cast_mat2x3.h"

namespace sgf {
    Mat2x3 & toSgf(glm::mat2x3 & value) {
        static_assert(sizeof(Mat2x3) == sizeof(glm::mat2x3));
        return reinterpret_cast<Mat2x3 &>(value);
    }

    const Mat2x3 & toSgf(const glm::mat2x3 & value) {
        static_assert(sizeof(Mat2x3) == sizeof(glm::mat2x3));
        return reinterpret_cast<const Mat2x3 &>(value);
    }
    
    glm::mat2x3 & toGlm(Mat2x3 & value) {
        static_assert(sizeof(Mat2x3) == sizeof(glm::mat2x3));
        return reinterpret_cast<glm::mat2x3 &>(value);
    }

    const glm::mat2x3 & toGlm(const Mat2x3 & value) {
        static_assert(sizeof(Mat2x3) == sizeof(glm::mat2x3));
        return reinterpret_cast<const glm::mat2x3 &>(value);
    }
}
