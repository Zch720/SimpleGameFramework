#pragma once

#include <sgf/utils/fwd.h>

namespace sgf_font {
    class FontRenderContext;
    
    class CharacterSet;
    class Character;
    
    class FontLoader;
    struct FontMetrics;

    class GlyphAtlas;
    class Glyph;

    struct FontTag;
    using FontId = sgf_core::ResourceId<FontTag>;
    class Font;
    
    class Text;
    class TextRenderer;
}
