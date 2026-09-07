#include "sgf/type/casting/cast_mat4x2.h"

namespace sgf {
    Mat4x2 & toSgf(glm::mat4x2 & value) {
        static_assert(sizeof(Mat4x2) == sizeof(glm::mat4x2));
        return reinterpret_cast<Mat4x2 &>(value);
    }

    const Mat4x2 & toSgf(const glm::mat4x2 & value) {
        static_assert(sizeof(Mat4x2) == sizeof(glm::mat4x2));
        return reinterpret_cast<const Mat4x2 &>(value);
    }
    
    glm::mat4x2 & toGlm(Mat4x2 & value) {
        static_assert(sizeof(Mat4x2) == sizeof(glm::mat4x2));
        return reinterpret_cast<glm::mat4x2 &>(value);
    }

    const glm::mat4x2 & toGlm(const Mat4x2 & value) {
        static_assert(sizeof(Mat4x2) == sizeof(glm::mat4x2));
        return reinterpret_cast<const glm::mat4x2 &>(value);
    }
}
