#pragma once

#include "sgf/context/text_render.h"

namespace sgf {
    template <class TextRenderT>
    class InternalTextRender {
        static_assert(std::is_same_v<TextRenderT, sgf::TextRender> || std::is_same_v<TextRenderT, const sgf::TextRender>,
            "Generic type of InternalRender must be Render or const Render");

    private:
        TextRenderT & textRender;

    public:
        InternalTextRender(TextRenderT & textRender);

        sgf_font::FontRenderContext & FontRenderContext();
        const sgf_font::FontRenderContext & FontRenderContext() const;
    };
}

#include "../../../templte_src/sgf/context/internal_text_render.tpp"
