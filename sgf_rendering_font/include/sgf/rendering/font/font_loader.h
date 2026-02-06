#pragma once

#include <memory>
#include "./character.h"
#include "./font_id.h"
#include "./font_metrics.h"

namespace sgf_font {
    class FontRenderContext;
    class Font;

    class FontLoader {
    private:
        friend FontRenderContext;

        struct LoaderImpl;

        FontRenderContext & context;
        std::unique_ptr<LoaderImpl> impl;

    public:
        FontLoader(FontRenderContext & context);
        ~FontLoader();

        FontMetrics getCurrentMetrics(const FontId & fontId) const;

        void addFont(const FontId & fontId, const std::string & filePath);
        void loadCharacter(const FontId & fontId, int size, CharacterCode code);
    };
}
