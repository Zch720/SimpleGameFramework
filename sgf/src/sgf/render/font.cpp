#include "sgf/render/font.h"
#include <sgf/rendering/font/font_render_context.h>
#include "sgf/context/render.h"
#include "sgf/context/internal_text_render.h"

namespace sgf {
    struct Font::Impl {
        sgf_font::FontId fontId;
    };

    Font::Font(const Contexts & contexts, const std::string & fontPath):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->fontId = InternalTextRender(this->contexts.get<TextRender>())
            .FontRenderContext()
            .addFont(fontPath);
    }

    Font::~Font() {
    }

    void Font::loadCharacters(int size, const std::vector<char32_t> & characters) {
        sgf_font::CharacterSet set;
        set.addGroup({
            .size = size,
            .characters = characters
        });
        InternalTextRender(this->contexts.get<TextRender>())
            .FontRenderContext()
            .getFont(impl->fontId)
            .loadCharacters(set);
    }

    void Font::update() {
        sgf_font::FontRenderContext & fontRenderContext = InternalTextRender(this->contexts.get<TextRender>())
            .FontRenderContext();
        fontRenderContext
            .getFont(impl->fontId)
            .updateAtlasTexture(fontRenderContext);
    }

    sgf_font::FontId Font::getFontId() const {
        return impl->fontId;
    }
}
