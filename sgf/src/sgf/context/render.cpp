#include "sgf/context/render.h"
#include "sgf/render/renderable.h"
#include <sgf/rendering/render_context.h>

namespace sgf {
    Render::Render(const Contexts & contexts):
        contexts(contexts),
        textRender(this->contexts)
    {
    }

    TextRender & Render::Text() {
        return textRender;
    }

    const TextRender & Render::Text() const {
        return textRender;
    }

    Shader Render::createShader(const std::string & vertexShader, const std::string & fragmentShader) {
        return Shader({ *this }, vertexShader, fragmentShader);
    }

    Material Render::createMaterial(const Shader & shader) {
        return Material({ *this }, shader.getShaderId());
    }

    Renderable Render::createRenderable(const Mesh & mesh, const Material & material) {
        return Renderable({ *this }, mesh.getMeshId(), material.getMaterialId());
    }

    sgf_core::RenderContext & Render::RenderContext() {
        return contexts.get<sgf_core::RenderContext>();
    }

    const sgf_core::RenderContext & Render::RenderContext() const {
        return contexts.get<sgf_core::RenderContext>();
    }

    Shader Render::createShader(const sgf_core::ShaderId & shaderId) {
        return Shader({ *this }, shaderId);
    }

    Material Render::createMaterial(const sgf_core::MaterialId & materialId) {
        return Material({ *this }, materialId);
    }

    Uniform Render::createUniform(const sgf_core::UniformId & uniformId) {
        return Uniform({ *this }, uniformId);
    }
}
