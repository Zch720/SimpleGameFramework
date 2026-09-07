#pragma once

#include <sgf/rendering/material_id.h>
#include <sgf/rendering/renderable_id.h>
#include "./text.h"

namespace sgf_font {
    class FontRenderContext;

    class TextRenderer {
    private:
        friend FontRenderContext;

        FontRenderContext & context;
        sgf_core::RenderableId renderableId;

        TextRenderer (FontRenderContext & context);

    public:
        void render(const Text & text, const sgf_core::MaterialId & materialId);
    };
}
