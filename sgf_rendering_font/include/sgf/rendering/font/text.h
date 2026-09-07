#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <sgf/rendering/material_id.h>
#include <sgf/rendering/mesh_id.h>
#include <sgf/rendering/transform.h>
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

        sgf_core::MeshId meshId;

        sgf_core::Transform transform;

        void updateMesh(FontRenderContext & context);

    public:
        Text(FontRenderContext & context, const FontId & fontId, const int size, const std::u32string & text);
    
        int getWidth() const;
        int getHeight() const;

        int getSize() const;
        const std::u32string & getText() const;
        FontId getFont() const;
        sgf_core::MeshId getMesh() const;

        sgf_core::Transform & getTransform();
        const sgf_core::Transform & getTransform() const;

        void setSize(int size);
        void setText(const std::u32string & text);
        void setFont(const FontId & fontId);

        void update(FontRenderContext & context);
    };
}
