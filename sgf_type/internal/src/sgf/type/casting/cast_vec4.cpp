#include "sgf/type/casting/cast_vec4.h"

namespace sgf {
    Vec4 & toSgf(glm::vec4 & value) {
        static_assert(sizeof(Vec4) == sizeof(glm::vec4));
        return reinterpret_cast<Vec4 &>(value);
    }

    const Vec4 & toSgf(const glm::vec4 & value) {
        static_assert(sizeof(Vec4) == sizeof(glm::vec4));
        return reinterpret_cast<const Vec4 &>(value);
    }

    glm::vec4 & toGlm(Vec4 & value) {
        static_assert(sizeof(Vec4) == sizeof(glm::vec4));
        return reinterpret_cast<glm::vec4 &>(value);
    }

    const glm::vec4 & toGlm(const Vec4 & value) {
        static_assert(sizeof(Vec4) == sizeof(glm::vec4));
        return reinterpret_cast<const glm::vec4 &>(value);
    }
}
