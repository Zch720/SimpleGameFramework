#include "sgf/type/casting/cast_vec2.h"

namespace sgf {
    Vec2 & toSgf(glm::vec2 & value) {
        static_assert(sizeof(Vec2) == sizeof(glm::vec2));
        return reinterpret_cast<Vec2 &>(value);
    }

    const Vec2 & toSgf(const glm::vec2 & value) {
        static_assert(sizeof(Vec2) == sizeof(glm::vec2));
        return reinterpret_cast<const Vec2 &>(value);
    }

    glm::vec2 & toGlm(Vec2 & value) {
        static_assert(sizeof(Vec2) == sizeof(glm::vec2));
        return reinterpret_cast<glm::vec2 &>(value);
    }

    const glm::vec2 & toGlm(const Vec2 & value) {
        static_assert(sizeof(Vec2) == sizeof(glm::vec2));
        return reinterpret_cast<const glm::vec2 &>(value);
    }
}
