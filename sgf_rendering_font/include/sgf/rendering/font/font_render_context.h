#pragma once

#include <unordered_map>
#include <glm/matrix.hpp>
#include <sgf/rendering/material_id.h>
#include <sgf/rendering/shader_id.h>
#include <sgf/utils/id_generator.h>
#include "./font.h"
#include "./font_id.h"
#include "./font_loader.h"
#include "./text_renderer.h"

namespace sgf_core {
    class RenderContext;
}

namespace sgf_font {
    class FontRenderContext {
    private:
        sgf_core::RenderContext & context;
        sgf_core::ShaderId defaultShaderId;
        sgf_core::MaterialId defaultMaterialId;

        FontLoader fontLoader;
        sgf_font::TextRenderer textRenderer;

        sgf_core::IdGenerator<FontId> fontIdGenerator;
        std::unordered_map<FontId, Font> fonts;

        uint32_t dpi;

    public:
        FontRenderContext(sgf_core::RenderContext & context);
        ~FontRenderContext();

        sgf_font::TextRenderer & TextRenderer();

        sgf_core::RenderContext & getContext();
        const sgf_core::RenderContext & getContext() const;

        Font & getFont(const FontId & fontId);
        const Font & getFont(const FontId & fontId) const;

        sgf_core::ShaderId getDefaultShaderId() const;
        sgf_core::MaterialId getDefaultMaterialId() const;

        void setMaterial(const sgf_core::MaterialId & materialId);

        uint32_t getDpi() const;
        void setDpi(const uint32_t dpi);

        FontId addFont(const std::string & filePath);

        void updateFontsAtlasTexture();
    };
}
