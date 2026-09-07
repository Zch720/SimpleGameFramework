#include "sgf/context/text_render.h"
#include <sgf/rendering/font/font_render_context.h>

namespace sgf {
    TextRender::TextRender(const Contexts & contexts):
        contexts(contexts)
    {
    }

    Font TextRender::createFont(const std::string & fontPath) {
        return Font({ *this }, fontPath);
    }

    Text TextRender::createText(const Material & material, const Font & font, int size, const std::u32string & text) {
        return Text(
            { *this },
            sgf_font::Text(contexts.get<sgf_font::FontRenderContext>(), font.getFontId(), size, text),
            material.getMaterialId()
        );
    }

    sgf_font::FontRenderContext & TextRender::FontRenderContext() {
        return contexts.get<sgf_font::FontRenderContext>();
    }

    const sgf_font::FontRenderContext & TextRender::FontRenderContext() const {
        return contexts.get<sgf_font::FontRenderContext>();
    }
}
