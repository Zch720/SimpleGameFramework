#include "../../../../include/sgf/rendering/font/glyph.h"

namespace sgf_font {
    Glyph::Glyph():
        code(0),
        size(),
        bearing(),
        advance(0)
    {
    }
    
    Glyph::Glyph(CharacterCode code, const glm::vec2 & size, const glm::vec2 & bearing, int32_t advance):
        code(code),
        size(size),
        bearing(bearing),
        advance(advance)
    {
    }

    CharacterCode Glyph::getCode() const {
        return code;
    }

    glm::vec2 Glyph::getSize() const {
        return size;
    }

    glm::vec2 Glyph::getBearing() const {
        return bearing;
    }

    int32_t Glyph::getAdvance() const {
        return advance;
    }
}
