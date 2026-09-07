#include "sgf/type/casting/cast_mat3x2.h"

namespace sgf {
    Mat3x2 & toSgf(glm::mat3x2 & value) {
        static_assert(sizeof(Mat3x2) == sizeof(glm::mat3x2));
        return reinterpret_cast<Mat3x2 &>(value);
    }

    const Mat3x2 & toSgf(const glm::mat3x2 & value) {
        static_assert(sizeof(Mat3x2) == sizeof(glm::mat3x2));
        return reinterpret_cast<const Mat3x2 &>(value);
    }
    
    glm::mat3x2 & toGlm(Mat3x2 & value) {
        static_assert(sizeof(Mat3x2) == sizeof(glm::mat3x2));
        return reinterpret_cast<glm::mat3x2 &>(value);
    }

    const glm::mat3x2 & toGlm(const Mat3x2 & value) {
        static_assert(sizeof(Mat3x2) == sizeof(glm::mat3x2));
        return reinterpret_cast<const glm::mat3x2 &>(value);
    }
}
