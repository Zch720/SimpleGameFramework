#pragma once

#include "sgf/contexts.h"
#include "sgf/core_fwd.h"
#include "sgf/render/font.h"
#include "sgf/render/material.h"
#include "sgf/render/text.h"

namespace sgf {
    template <class TextRenderT>
    class InternalTextRender;
    class Render;

    class TextRender {
    public:
        using Contexts = sgf::Contexts<
            sgf_font::FontRenderContext
        >;

    private:
        friend InternalTextRender<TextRender>;
        friend InternalTextRender<const TextRender>;
        friend Render;

        Contexts contexts;

        TextRender(const Contexts & contexts);

        sgf_font::FontRenderContext & FontRenderContext();
        const sgf_font::FontRenderContext & FontRenderContext() const;

    public:
        Font createFont(const std::string & fontPath);
        Text createText(const Material & material, const Font & font, int size, const std::u32string & text);
    };
}
