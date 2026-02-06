#include "../../../../include/sgf/rendering/font/font.h"
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>
#include "../../../../include/sgf/rendering/font/font_render_context.h"

namespace sgf_font {
    std::string FontTag::TypeName = "Font";

    Font::Font(const FontId & id, FontLoader & fontLoader):
        id(id),
        fontLoader(fontLoader)
    {
    }

    FontMetrics Font::getMetrics(int size) const {
        if (atlases.find(size) == atlases.end()) {
            fontLoader.loadCharacter(id, size, 'a');
        }
        return atlases.at(size).getMetrics();
    }

    sgf_core::Texture2DId Font::getTextureId(int size) const {
        if (atlases.find(size) == atlases.end()) {
            SGF_LOG_ERROR("Try to get font texture with id: {}, size: {}. But glyph atlas not found.", id.toString(), size);
            throw sgf_core::ResourceNotFound("Try to get font texture with id: " + id.toString() + ", size: " + std::to_string(size) + ". But glyph atlas not found.");
        }
        return atlases.at(size).getTextureId();
    }
    
    const Glyph & Font::getGlyph(int size, CharacterCode code) const {
        if (atlases.find(size) == atlases.end() || !atlases.at(size).hasCharacter(code)) {
            fontLoader.loadCharacter(id, size, code);
        }

        return atlases.at(size).getGlyph(code);
    }

    const glm::vec4 & Font::getGlyphNormalizedUV(int size, CharacterCode code) const {
        if (atlases.find(size) == atlases.end()) {
            SGF_LOG_ERROR("Try to get font character uv with id: {}, size: {}, code: {}. But glyph atlas not found.", id.toString(), size, code);
            throw sgf_core::ResourceNotFound("Try to get font texture with id: " + id.toString() + ", size: " + std::to_string(size) + ". code: " + std::to_string(code) + ". But glyph atlas not found.");
        }
        return atlases.at(size).getGlyphNormalizedUV(code);
    }

    void Font::loadCharacters(const CharacterSet & characterSet) {
        for (const CharacterSet::CharacterGroup & group : characterSet.getGroups()) {
            for (const CharacterCode & code : group.characters) {
                fontLoader.loadCharacter(id, group.size, code);
            }
        }
    }

    void Font::addGlyph(FontRenderContext & context, int size, const Glyph & glyph, const std::vector<uint8_t> & data) {
        if (atlases.find(size) == atlases.end()) {
            atlases.insert(std::make_pair(size, GlyphAtlas(context, size * 72 / context.getDpi(), fontLoader.getCurrentMetrics(id))));
        }
        atlases.at(size).addGlyph(glyph, data);
    }

    void Font::updateAtlasTexture(FontRenderContext & context) {
        for (auto & [size, atlas] : atlases) {
            atlas.updateAtlasTexture(context);
        }
    }
}
