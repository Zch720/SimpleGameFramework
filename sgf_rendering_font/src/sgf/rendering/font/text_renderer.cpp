#include "sgf/rendering/font/text_renderer.h"
#include <sgf/rendering/render_context.h>
#include "sgf/rendering/font/font_render_context.h"

namespace sgf_font {
    TextRenderer::TextRenderer(FontRenderContext & context):
        context(context)
    {
        renderableId = context.getContext().RenderableManager().create({
            .meshId = {},
            .materialId = {}
        });
    }

    void TextRenderer::render(const Text & text, const sgf_core::MaterialId & materialId) {
        context.getContext().MaterialManager()
            .getRef(materialId)
            .setTextureId(context.getFont(text.getFont()).getTextureId(text.getSize()));

        sgf_core::Renderable & renderable = context.getContext().RenderableManager().getRef(renderableId);
        renderable.setMeshId(text.getMesh());
        renderable.setMaterialId(materialId);
        renderable.setTransform(text.getTransform());
        renderable.render(context.getContext());
    }
}
