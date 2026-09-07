#include "sgf/ui.h"
#include <sgf/rendering/font/font_render_context.h>
#include <sgf/rendering/render_context.h>
#include <sgf/type/casting/cast_mat4.h>
#include "sgf/context/internal_render.h"
#include "sgf/context/internal_text_render.h"

namespace sgf {
    struct UI::Impl {
        sgf_core::Projection projection;
    };

    UI::UI(const UIContexts & contexts):
        contexts(contexts),
        size(0, 0),
        uiTextMaterial(
            this->contexts.get<Render>().createMaterial(
                InternalRender(this->contexts.get<Render>())
                    .createShader(
                        InternalTextRender(this->contexts.get<Render>().Text()).FontRenderContext().getDefaultShaderId()
                    )
            )
        )
    {
        impl = std::make_unique<Impl>();
        createProjection();
        createUITextMaterial();
    }

    UI::UI(const UIContexts & contexts, const Rect & size):
        contexts(contexts),
        size(size),
        uiTextMaterial(
            this->contexts.get<Render>().createMaterial(
                InternalRender(this->contexts.get<Render>())
                    .createShader(
                        InternalTextRender(this->contexts.get<Render>().Text())
                            .FontRenderContext()
                            .getDefaultShaderId()
                    )
            )
        )
    {
        impl = std::make_unique<Impl>();
        createProjection();
        createUITextMaterial();
    }

    UI::~UI() {
    }

    Rect UI::getSize() const {
        return size;
    }

    void UI::setSize(const Rect & size) {
        this->size = size;
        impl->projection.width(size.width);
        impl->projection.height(size.height);
    }

    Text UI::createText(const Font & font, int size, const std::u32string & text) {
        return contexts.get<Render>().Text().createText(uiTextMaterial, font, size, text);
    }

    void UI::createProjection() {
        impl->projection = sgf_core::Projection({
            .type = sgf_core::Projection::Type::ORTHOGRAPHIC,
            .width = size.width,
            .height = size.height,
            .near = -1000,
            .far = 1000
        });
    }

    void UI::createUITextMaterial() {
        uiTextMaterial.useTexture(true);

        uiTextMaterial.registerUniform("view", UniformSource::CAMERA_VIEW);
        uiTextMaterial.registerUniform("transform", UniformSource::TRANSFORM);
        uiTextMaterial.registerUniform("textColor", UniformSource::RENDERABLE_COLOR);
        std::optional<Uniform> uniform = uiTextMaterial.registerUniform("projection", UniformSource::CUSTOM);
        
        if (uniform.has_value()) {
            uniform.value()
                .setGlobalProvider([this]() {
                    return toSgf(impl->projection.getProjectionMatrix());
                });
        }
    }
}
