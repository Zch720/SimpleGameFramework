#include "sgf/type/casting/cast_vec3.h"

namespace sgf {
    Vec3 & toSgf(glm::vec3 & value) {
        static_assert(sizeof(Vec3) == sizeof(glm::vec3));
        return reinterpret_cast<Vec3 &>(value);
    }

    const Vec3 & toSgf(const glm::vec3 & value) {
        static_assert(sizeof(Vec3) == sizeof(glm::vec3));
        return reinterpret_cast<const Vec3 &>(value);
    }

    glm::vec3 & toGlm(Vec3 & value) {
        static_assert(sizeof(Vec3) == sizeof(glm::vec3));
        return reinterpret_cast<glm::vec3 &>(value);
    }

    const glm::vec3 & toGlm(const Vec3 & value) {
        static_assert(sizeof(Vec3) == sizeof(glm::vec3));
        return reinterpret_cast<const glm::vec3 &>(value);
    }
}
