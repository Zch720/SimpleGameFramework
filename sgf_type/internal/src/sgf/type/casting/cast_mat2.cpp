#include "sgf/type/casting/cast_mat2.h"

namespace sgf {
    Mat2 & toSgf(glm::mat2 & value) {
        static_assert(sizeof(Mat2) == sizeof(glm::mat2));
        return reinterpret_cast<Mat2 &>(value);
    }

    const Mat2 & toSgf(const glm::mat2 & value) {
        static_assert(sizeof(Mat2) == sizeof(glm::mat2));
        return reinterpret_cast<const Mat2 &>(value);
    }
    
    glm::mat2 & toGlm(Mat2 & value) {
        static_assert(sizeof(Mat2) == sizeof(glm::mat2));
        return reinterpret_cast<glm::mat2 &>(value);
    }

    const glm::mat2 & toGlm(const Mat2 & value) {
        static_assert(sizeof(Mat2) == sizeof(glm::mat2));
        return reinterpret_cast<const glm::mat2 &>(value);
    }
}
