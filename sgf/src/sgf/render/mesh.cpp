#include "sgf/render/mesh.h"
#include <sgf/rendering/render_context.h>
#include "sgf/context/render.h"
#include "sgf/context/internal_render.h"

namespace sgf {
    struct Mesh::Impl {
        sgf_core::MeshId meshId;
    };

    Mesh::Mesh(const Contexts & contexts, const std::vector<uint8_t> & vertices, const std::vector<uint32_t> & indices, const sgf_core::VertexLayout & vertexLayout):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->meshId = InternalRender(this->contexts.get<Render>())
            .RenderContext()
            .MeshManager()
            .create({
                .vertices = (void *)vertices.data(),
                .verticesCount = vertices.size() / vertexLayout.getStride(),
                .indices = (uint32_t *)indices.data(),
                .indicesCount = indices.size(),
                .vertexLayout = vertexLayout
            });
    }

    Mesh::~Mesh() {
    }

    sgf_core::MeshId Mesh::getMeshId() const {
        return impl->meshId;
    }
}
