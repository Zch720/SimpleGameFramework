#pragma once

#include <unordered_map>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <sgf/rendering/texture_2d_data.h>
#include <sgf/rendering/texture_2d_id.h>
#include "./font_metrics.h"
#include "./glyph.h"

namespace sgf_font {
    class FontRenderContext;

    class GlyphAtlas {
    private:
        bool atlasSizeDirty;
        bool atlasDirty;

        FontMetrics metrics;

        int32_t atlasColumnCounter;
        int32_t atlasRowCounter;
        int32_t atlasCurrentRowHeight;

        std::unordered_map<CharacterCode, Glyph> glyphs;
        sgf_core::Texture2DData textureData;
        sgf_core::Texture2DId textureId;

        std::unordered_map<CharacterCode, glm::ivec4> atlasUVs;
        std::unordered_map<CharacterCode, glm::vec4> normalizedUVs;

        void copyGlyphData(const glm::vec2 & pos, const glm::vec2 & size, const std::vector<uint8_t> & data);
        void normalizeAtlasUV();

    public:
        GlyphAtlas(FontRenderContext & context, int32_t pixelSize, FontMetrics metrics);

        bool hasCharacter(CharacterCode code) const;

        FontMetrics getMetrics() const;
        sgf_core::Texture2DId getTextureId() const;
        const Glyph & getGlyph(CharacterCode code) const;
        const glm::vec4 & getGlyphNormalizedUV(CharacterCode code) const;

        void addGlyph(const Glyph & glyph, const std::vector<uint8_t> & data);
        void updateAtlasTexture(FontRenderContext & context);
    };
}
