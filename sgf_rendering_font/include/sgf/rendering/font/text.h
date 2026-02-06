#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <sgf/rendering/material_id.h>
#include <sgf/rendering/mesh_id.h>
#include <sgf/rendering/renderable_id.h>
#include "./font_id.h"

namespace sgf_font {
    class FontRenderContext;

    class Text {
    private:
        bool textDirty;

        int size;
        std::u32string text;
        FontId fontId;

        int width;
        int height;

        bool positionDirty;
        glm::vec3 positionValue;

        sgf_core::MeshId meshId;
        sgf_core::RenderableId renderableId;

        void updateMesh(FontRenderContext & context);

    public:
        Text(FontRenderContext & context, const FontId & fontId, const int size, const std::u32string & text);
    
        int getWidth() const;
        int getHeight() const;

        int getSize() const;
        const std::u32string & getText() const;
        FontId getFont() const;

        void setSize(int size);
        void setText(const std::u32string & text);
        void setFont(const FontId & fontId);

        void update(FontRenderContext & context);
        void render(const FontRenderContext & context) const;

        glm::vec3 position() const;
        void position(const glm::vec3 & position);
        void translate(const glm::vec3 & translation);
        void translateX(const float translation);
        void translateY(const float translation);
        void translateZ(const float translation);
    };
}
