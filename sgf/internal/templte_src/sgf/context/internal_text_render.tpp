#include "sgf/context/internal_text_render.h"

namespace sgf {
    template <class TextRenderT>
    InternalTextRender<TextRenderT>::InternalTextRender(TextRenderT & textRender):
        textRender(textRender)
    {
    }

    template <class TextRenderT>
    sgf_font::FontRenderContext & InternalTextRender<TextRenderT>::FontRenderContext() {
        return textRender.FontRenderContext();
    }

    template <class TextRenderT>
    const sgf_font::FontRenderContext & InternalTextRender<TextRenderT>::FontRenderContext() const {
        return textRender.FontRenderContext();
    }
}
