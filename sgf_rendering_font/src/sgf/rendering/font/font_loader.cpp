#include "../../../../include/sgf/rendering/font/font_loader.h"
#include <ft2build.h>
#include <sgf/utils/exceptions/initialization_failed.h>
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>
#include FT_FREETYPE_H
#include "../../../../include/sgf/rendering/font/font_render_context.h"

namespace sgf_font {
    struct FontLoader::LoaderImpl {
        FT_Library ftLibrary;
        std::unordered_map<FontId, FT_Face> faces;
    };

    FontLoader::FontLoader(FontRenderContext & context):
        context(context)
    {
        impl = std::make_unique<LoaderImpl>();

        if (FT_Init_FreeType(&impl->ftLibrary)) {
            SGF_LOG_ERROR("Failed to initialize FreeType Library.");
            throw sgf_core::InitializationFailed("Failed to initialize FreeType Library.");
        }
    }

    FontLoader::~FontLoader() {
        for (auto & [fontId, face] : impl->faces) {
            FT_Done_Face(face);
        }
        FT_Done_FreeType(impl->ftLibrary);
    }

    FontMetrics FontLoader::getCurrentMetrics(const FontId & fontId) const {
        // return impl->faces[fontId]->size->metrics.descender / 64;
        FT_Size_Metrics & metrics = impl->faces[fontId]->size->metrics;
        return {
            .ascent = metrics.ascender / 64,
            .descent = metrics.descender / 64,
            .lineGap = (metrics.height - metrics.ascender + metrics.descender) / 64
        };
    }

    void FontLoader::addFont(const FontId & fontId, const std::string & filePath) {
        impl->faces.insert(std::make_pair(fontId, nullptr));
        if (FT_New_Face(impl->ftLibrary, filePath.c_str(), 0, &impl->faces[fontId])) {
            SGF_LOG_ERROR("Failed to load font at path {}.", filePath);
            throw sgf_core::InitializationFailed("Failed to load font at path " + filePath + ".");
        }
    }

    void FontLoader::loadCharacter(const FontId & fontId, int size, CharacterCode code) {
        if (impl->faces.find(fontId) == impl->faces.end()) {
            SGF_LOG_ERROR("Try to add character to font with {}, but FT_Face not found", fontId.toString());
            throw sgf_core::ResourceNotFound("Try to add character to font with " + fontId.toString() + ", but FT_Face not found");
        }
        
        FT_Face & face = impl->faces[fontId];
        if (FT_Set_Char_Size(face, 0, size * 64, context.getDpi(), context.getDpi())) {
            SGF_LOG_ERROR("Failed to set character raw data size.");
            throw std::runtime_error("Failed to set character raw data size.");
        }
        if (FT_Load_Char(face, code, FT_LOAD_RENDER)) {
            SGF_LOG_ERROR("Failed to load Glyph for '{}'", code);
            throw std::runtime_error("Failed to load Glyph for '" + std::to_string(code) + "'");
        }
        context.getFont(fontId).addGlyph(
            context,
            size,
            Glyph(
                code,
                { face->glyph->bitmap.width, face->glyph->bitmap.rows },
                { face->glyph->bitmap_left, face->glyph->bitmap_top },
                face->glyph->advance.x / 64),
            { face->glyph->bitmap.buffer, face->glyph->bitmap.buffer + face->glyph->bitmap.width * face->glyph->bitmap.rows }
        );
    }
}
