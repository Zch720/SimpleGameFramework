#pragma once

#include "./character.h"
#include <glm/vec2.hpp>

namespace sgf_font {
    class Glyph {
    private:
        CharacterCode code;
        glm::vec2 size;
        glm::vec2 bearing;
        int32_t advance;

    public:
        Glyph();
        Glyph(CharacterCode code, const glm::vec2 & size, const glm::vec2 & bearing, int32_t advance);

        CharacterCode getCode() const;
        glm::vec2 getSize() const;
        glm::vec2 getBearing() const;
        int32_t getAdvance() const;
    };
}
