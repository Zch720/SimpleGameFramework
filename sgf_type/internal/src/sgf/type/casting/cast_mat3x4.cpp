#include "sgf/type/casting/cast_mat3x4.h"

namespace sgf {
    Mat3x4 & toSgf(glm::mat3x4 & value) {
        static_assert(sizeof(Mat3x4) == sizeof(glm::mat3x4));
        return reinterpret_cast<Mat3x4 &>(value);
    }

    const Mat3x4 & toSgf(const glm::mat3x4 & value) {
        static_assert(sizeof(Mat3x4) == sizeof(glm::mat3x4));
        return reinterpret_cast<const Mat3x4 &>(value);
    }
    
    glm::mat3x4 & toGlm(Mat3x4 & value) {
        static_assert(sizeof(Mat3x4) == sizeof(glm::mat3x4));
        return reinterpret_cast<glm::mat3x4 &>(value);
    }

    const glm::mat3x4 & toGlm(const Mat3x4 & value) {
        static_assert(sizeof(Mat3x4) == sizeof(glm::mat3x4));
        return reinterpret_cast<const glm::mat3x4 &>(value);
    }
}
