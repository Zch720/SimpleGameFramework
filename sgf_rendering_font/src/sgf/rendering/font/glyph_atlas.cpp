#include "../../../../include/sgf/rendering/font/glyph_atlas.h"
#include <sgf/rendering/render_context.h>
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>
#include "../../../../include/sgf/rendering/font/font_render_context.h"

namespace sgf_font {
    GlyphAtlas::GlyphAtlas(FontRenderContext & context, int32_t pixelSize, FontMetrics metrics):
        atlasSizeDirty(false),
        atlasDirty(false),
        metrics(metrics),
        atlasColumnCounter(0),
        atlasRowCounter(0),
        atlasCurrentRowHeight(0)
    {
        textureData = {
            .internalFormat = sgf_core::TextureFormat::RED,
            .dataFormat = sgf_core::TextureFormat::RED,
            .width = pixelSize * 32,
            .height = pixelSize * 8,
            .dataType = sgf_core::TextureDataType::UNSIGNED_BYTE
        };
        textureData.data.resize(textureData.width * textureData.height, 0);

        textureId = context.getContext().Texture2DManager.create({
            .type = sgf_core::ResourceType::DYNAMIC,
            .data = textureData
        });

        context.getContext().unsafeExecute([this](const sgf_core::UnsafeGLContext & unsafeContext) {
            uint32_t textureHandle = unsafeContext.getTexture2DTextureHandle(textureId);

            glBindTexture(GL_TEXTURE_2D, textureHandle);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
        });
    }
    
    bool GlyphAtlas::hasCharacter(CharacterCode code) const {
        return glyphs.find(code) != glyphs.end();
    }

    FontMetrics GlyphAtlas::getMetrics() const {
        return metrics;
    }

    sgf_core::Texture2DId GlyphAtlas::getTextureId() const {
        return textureId;
    }

    const Glyph & GlyphAtlas::getGlyph(CharacterCode code) const {
        if (glyphs.find(code) == glyphs.end()) {
            SGF_LOG_ERROR("Try to get glyph with code: {}, but not found.", code);
            throw sgf_core::ResourceNotFound("Try to get glyph with code: " + std::to_string(code) + ", but not found.");
        }
        return glyphs.at(code);
    }

    const glm::vec4 & GlyphAtlas::getGlyphNormalizedUV(CharacterCode code) const {
        if (normalizedUVs.find(code) == normalizedUVs.end()) {
            SGF_LOG_ERROR("Try to get glyph uv with code: {}, but not found.", code);
            throw sgf_core::ResourceNotFound("Try to get glyph uv with code: " + std::to_string(code) + ", but not found.");
        }
        return normalizedUVs.at(code);
    }

    void GlyphAtlas::addGlyph(const Glyph & glyph, const std::vector<uint8_t> & data) {
        atlasDirty = true;

        if (glyph.getSize().x + atlasColumnCounter > textureData.width) {
            atlasRowCounter += atlasCurrentRowHeight;
            atlasColumnCounter = 0;
            atlasCurrentRowHeight = glyph.getSize().y;
        }

        if (glyph.getSize().y + atlasRowCounter > textureData.height) {
            textureData.data.insert(textureData.data.end(), textureData.width * textureData.height, 0);
            textureData.height *= 2;
            atlasSizeDirty = true;
        }

        glyphs.insert(std::make_pair(glyph.getCode(), glyph));
        atlasUVs.insert(std::make_pair(glyph.getCode(), glm::vec4(atlasColumnCounter, atlasRowCounter, glyph.getSize().x, glyph.getSize().y)));
        normalizedUVs.insert(std::make_pair(glyph.getCode(), glm::vec4(
            (float)atlasColumnCounter / textureData.width, (float)(atlasRowCounter) / textureData.height,
            (float)glyph.getSize().x / textureData.width, (float)glyph.getSize().y / textureData.height
        )));

        copyGlyphData({ atlasColumnCounter, atlasRowCounter }, glyph.getSize(), data);
        atlasColumnCounter += glyph.getSize().x;
        atlasCurrentRowHeight = std::max(atlasCurrentRowHeight, (int)glyph.getSize().y);


        if (atlasSizeDirty) {
            normalizeAtlasUV();
            atlasSizeDirty = false;
        }
    }

    void GlyphAtlas::updateAtlasTexture(FontRenderContext & context) {
        if (atlasDirty) {
            context.getContext().Texture2DManager.getRef(textureId).updateData(textureData);
            atlasDirty = false;
        }
    }

    void GlyphAtlas::copyGlyphData(const glm::vec2 & pos, const glm::vec2 & size, const std::vector<uint8_t> & data) {
        for (int y = 0, textureDataPos, dataPos; y < size.y; y++) {
            textureDataPos = (pos.y + y) * textureData.width + pos.x;
            dataPos = size.x * y;
            for (int x = 0; x < size.x; x++, textureDataPos++, dataPos++) {
                textureData.data[textureDataPos] = data[dataPos];
            }
        }
    }

    void GlyphAtlas::normalizeAtlasUV() {
        for (const auto & [code, atlasUV] : atlasUVs) {
            glm::vec4 & normalized = normalizedUVs.at(code);
            normalized.x = (float)atlasUV.x / textureData.width;
            normalized.y = (float)(atlasUV.y) / textureData.height;
            normalized.z = (float)atlasUV.z / textureData.width;
            normalized.w = (float)atlasUV.w / textureData.height;
        }
    }
}
