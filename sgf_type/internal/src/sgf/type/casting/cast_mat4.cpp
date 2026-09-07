#include "sgf/type/casting/cast_mat4.h"

namespace sgf {
    Mat4 & toSgf(glm::mat4 & value) {
        static_assert(sizeof(Mat4) == sizeof(glm::mat4));
        return reinterpret_cast<Mat4 &>(value);
    }

    const Mat4 & toSgf(const glm::mat4 & value) {
        static_assert(sizeof(Mat4) == sizeof(glm::mat4));
        return reinterpret_cast<const Mat4 &>(value);
    }
    
    glm::mat4 & toGlm(Mat4 & value) {
        static_assert(sizeof(Mat4) == sizeof(glm::mat4));
        return reinterpret_cast<glm::mat4 &>(value);
    }

    const glm::mat4 & toGlm(const Mat4 & value) {
        static_assert(sizeof(Mat4) == sizeof(glm::mat4));
        return reinterpret_cast<const glm::mat4 &>(value);
    }
}
