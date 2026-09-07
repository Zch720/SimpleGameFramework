#include "sgf/render/renderable.h"
#include <sgf/rendering/render_context.h>
#include "sgf/context/render.h"
#include "sgf/context/internal_render.h"

namespace sgf {
    struct Renderable::Impl {
        sgf_core::RenderableId renderableId;
        sgf_core::Transform transform;
    };

    Renderable::Renderable(const Contexts & contexts, const sgf_core::MeshId & meshId, const sgf_core::MaterialId & materialId):
        contexts(contexts),
        impl(std::make_shared<Impl>()),
        transform(impl->transform)
    {
        impl->renderableId = InternalRender(this->contexts.get<Render>())
            .RenderContext()
            .RenderableManager()
            .create({
                .meshId = meshId,
                .materialId = materialId
            });
    }

    Renderable::~Renderable() {
    }
    
    sgf::Transform & Renderable::Transform() {
        return transform;
    }

    const sgf::Transform & Renderable::Transform() const {
        return transform;
    }

    void Renderable::update() {
        transform.update();
    }

    void Renderable::render() {
        sgf_core::RenderContext & renderContext = InternalRender(contexts.get<Render>())
            .RenderContext();
        renderContext
            .RenderableManager()
            .getRef(getRenderableId())
            .setTransform(impl->transform);
        renderContext
            .RenderableManager()
            .getRef(getRenderableId())
            .render(renderContext);
    }

    sgf_core::RenderableId Renderable::getRenderableId() const {
        return impl->renderableId;
    }
}
