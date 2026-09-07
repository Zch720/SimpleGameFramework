#include "../../../../include/sgf/rendering/font/text.h"
#include <sgf/rendering/render_context.h>
#include "../../../../include/sgf/rendering/font/font_render_context.h"

namespace sgf_font {
    Text::Text(FontRenderContext & context, const FontId & fontId, const int size, const std::u32string & text):
        textDirty(false),
        size(size),
        text(text),
        fontId(fontId)
    {
        sgf_core::VertexLayout layout;
        layout.addAttribute({ .index = 0, .size = 2, .type = sgf_core::VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });
        layout.addAttribute({ .index = 1, .size = 2, .type = sgf_core::VertexLayout::VertexType::FLOAT, .normalized = false, .offset = layout.getStride() });

        meshId = context.getContext().MeshManager().create({
            .type = sgf_core::ResourceType::DYNAMIC,
            .vertices = nullptr,
            .verticesCount = 0,
            .indices = nullptr,
            .indicesCount = 0,
            .vertexLayout = layout
        });

        updateMesh(context);
    }

    int Text::getWidth() const {
        return width;
    }

    int Text::getHeight() const {
        return height;
    }

    int Text::getSize() const {
        return size;
    }

    const std::u32string & Text::getText() const {
        return text;
    }

    FontId Text::getFont() const {
        return fontId;
    }

    sgf_core::MeshId Text::getMesh() const {
        return meshId;
    }

    sgf_core::Transform & Text::getTransform() {
        return transform;
    }

    const sgf_core::Transform & Text::getTransform() const {
        return transform;
    }

    void Text::setSize(int size) {
        this->size = size;
        textDirty = true;
    }

    void Text::setText(const std::u32string & text) {
        this->text = text;
        textDirty = true;
    }

    void Text::setFont(const FontId & fontId) {
        this->fontId = fontId;
        textDirty = true;
    }

    void Text::update(FontRenderContext & context) {
        transform.updateTransformationMatrix();

        if (textDirty) {
            updateMesh(context);
            textDirty = false;
        }
    }

    void Text::updateMesh(FontRenderContext & context) {
        std::vector<float> vertices;
        std::vector<uint32_t> indices;

        uint32_t indicesCounter = 0;
        FontMetrics metrics = context.getFont(fontId).getMetrics(size);
        width = 0;
        height = metrics.ascent - metrics.descent;
        for (int i = 0; i < text.size(); i++, indicesCounter += 4) {
            const Glyph & glyph = context.getFont(fontId).getGlyph(size, text[i]);
            const glm::vec4 & uv = context.getFont(fontId).getGlyphNormalizedUV(size, text[i]);
            glm::vec2 pos = { uv.x, uv.y };
            glm::vec2 size = { uv.z, uv.w };

            vertices.insert(vertices.end(), {
                width + glyph.getBearing().x, glyph.getBearing().y - metrics.descent, pos.x, pos.y,
                width + glyph.getBearing().x, glyph.getBearing().y - glyph.getSize().y - metrics.descent, pos.x, pos.y + size.y,
                width + glyph.getBearing().x + glyph.getSize().x, glyph.getBearing().y - glyph.getSize().y - metrics.descent, pos.x + size.x, pos.y + size.y,
                width + glyph.getBearing().x + glyph.getSize().x, glyph.getBearing().y - metrics.descent, pos.x + size.x, pos.y,
            });
            indices.insert(indices.end(), {
                indicesCounter, indicesCounter + 1, indicesCounter + 2,
                indicesCounter, indicesCounter + 2, indicesCounter + 3
            });
            width += glyph.getAdvance();
        }

        context.getContext().MeshManager()
            .getRef(meshId)
            .updateVertices(vertices.data(), vertices.size() / 4);
        context.getContext().MeshManager()
            .getRef(meshId)
            .updateIndices(indices.data(), indices.size());
    }
}
