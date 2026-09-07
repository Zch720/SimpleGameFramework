#include "sgf/render/text.h"
#include <sgf/rendering/font/font_render_context.h>
#include <sgf/rendering/font/text.h>
#include <sgf/rendering/material_id.h>
#include "sgf/context/text_render.h"
#include "sgf/context/internal_text_render.h"

namespace sgf {
    struct Text::Impl {
        sgf_font::Text text;
        sgf_core::MaterialId materialId;

        Impl(const sgf_font::Text & text, const sgf_core::MaterialId & materialId):
            text(text),
            materialId(materialId)
        {
        }
    };

    Text::Text(const Contexts & contexts, const sgf_font::Text & text, const sgf_core::MaterialId & materialId):
        contexts(contexts),
        impl(std::make_shared<Impl>(text, materialId)),
        transform(impl->text.getTransform())
    {
    }

    Text::~Text() {
    }

    sgf::Transform & Text::Transform() {
        return transform;
    }

    const sgf::Transform & Text::Transform() const {
        return transform;
    }

    int Text::getWidth() const {
        return impl->text.getWidth();
    }

    int Text::getHeight() const {
        return impl->text.getHeight();
    }

    int Text::getSize() const {
        return impl->text.getSize();
    }

    const std::u32string & Text::getText() const {
        return impl->text.getText();
    }

    void Text::setSize(int size) {
        impl->text.setSize(size);
    }

    void Text::setText(const std::u32string & text) {
        impl->text.setText(text);
    }

    void Text::update() {
        impl->text.update(
            InternalTextRender(contexts.get<TextRender>())
                .FontRenderContext()
        );
    }

    void Text::render() {
        InternalTextRender(contexts.get<TextRender>())
            .FontRenderContext()
            .TextRenderer()
            .render(impl->text, impl->materialId);
    }
}
