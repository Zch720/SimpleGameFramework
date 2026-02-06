#pragma once

#include <unordered_map>
#include "./character_set.h"
#include "./font_id.h"
#include "./font_loader.h"
#include "./font_metrics.h"
#include "./glyph_atlas.h"

namespace sgf_font {
    class FontRenderContext;

    class Font {
    private:
        FontId id;
        FontLoader & fontLoader;

        std::unordered_map<int, GlyphAtlas> atlases;
        
    public:
        Font(const FontId & id, FontLoader & fontLoader);

        FontMetrics getMetrics(int size) const;
        sgf_core::Texture2DId getTextureId(int size) const;
        const Glyph & getGlyph(int size, CharacterCode code) const;
        const glm::vec4 & getGlyphNormalizedUV(int size, CharacterCode code) const;

        void loadCharacters(const CharacterSet & characterSet);
        void addGlyph(FontRenderContext & context, int size, const Glyph & glyph, const std::vector<uint8_t> & data);
        void updateAtlasTexture(FontRenderContext & context);
    };
}
