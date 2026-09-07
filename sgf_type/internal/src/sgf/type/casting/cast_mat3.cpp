#include "sgf/type/casting/cast_mat3.h"

namespace sgf {
    Mat3 & toSgf(glm::mat3 & value) {
        static_assert(sizeof(Mat3) == sizeof(glm::mat3));
        return reinterpret_cast<Mat3 &>(value);
    }

    const Mat3 & toSgf(const glm::mat3 & value) {
        static_assert(sizeof(Mat3) == sizeof(glm::mat3));
        return reinterpret_cast<const Mat3 &>(value);
    }
    
    glm::mat3 & toGlm(Mat3 & value) {
        static_assert(sizeof(Mat3) == sizeof(glm::mat3));
        return reinterpret_cast<glm::mat3 &>(value);
    }

    const glm::mat3 & toGlm(const Mat3 & value) {
        static_assert(sizeof(Mat3) == sizeof(glm::mat3));
        return reinterpret_cast<const glm::mat3 &>(value);
    }
}
