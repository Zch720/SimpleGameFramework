#pragma once

#include "sgf/contexts.h"
#include "sgf/context/text_render.h"
#include "sgf/core_fwd.h"
#include "sgf/render/material.h"
#include "sgf/render/mesh.h"
#include "sgf/render/renderable.h"
#include "sgf/render/shader.h"
#include "sgf/render/uniform.h"
#include "sgf/render/vertex_layout.h"

namespace sgf {
    template <class RenderT>
    class InternalRender;

    class Render {
    public:
        using Contexts = sgf::Contexts<
            sgf_core::RenderContext,
            sgf_font::FontRenderContext
        >;

    private:
        friend InternalRender<Render>;
        friend InternalRender<const Render>;

        Contexts contexts;

        TextRender textRender;

        sgf_core::RenderContext & RenderContext();
        const sgf_core::RenderContext & RenderContext() const;

        Shader createShader(const sgf_core::ShaderId & shaderId);
        Material createMaterial(const sgf_core::MaterialId & materialId);
        Uniform createUniform(const sgf_core::UniformId & uniformId);

    public:
        Render(const Contexts & contexts);

        TextRender & Text();
        const TextRender & Text() const;

        Shader createShader(const std::string & vertexShader, const std::string & fragmentShader);
        Material createMaterial(const Shader & shader);
        template <typename Vertex>
        Mesh createMesh(const std::vector<Vertex> vertices, const std::vector<uint32_t> indices);
        Renderable createRenderable(const Mesh & mesh, const Material & material);
    };
}

#include "../../../template_src/sgf/context/render.tpp"
