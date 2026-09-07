#include "sgf/type/casting/cast_mat4x3.h"

namespace sgf {
    Mat4x3 & toSgf(glm::mat4x3 & value) {
        static_assert(sizeof(Mat4x3) == sizeof(glm::mat4x3));
        return reinterpret_cast<Mat4x3 &>(value);
    }

    const Mat4x3 & toSgf(const glm::mat4x3 & value) {
        static_assert(sizeof(Mat4x3) == sizeof(glm::mat4x3));
        return reinterpret_cast<const Mat4x3 &>(value);
    }
    
    glm::mat4x3 & toGlm(Mat4x3 & value) {
        static_assert(sizeof(Mat4x3) == sizeof(glm::mat4x3));
        return reinterpret_cast<glm::mat4x3 &>(value);
    }

    const glm::mat4x3 & toGlm(const Mat4x3 & value) {
        static_assert(sizeof(Mat4x3) == sizeof(glm::mat4x3));
        return reinterpret_cast<const glm::mat4x3 &>(value);
    }
}
