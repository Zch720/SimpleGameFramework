#include "sgf/context/internal_render.h"

namespace sgf {
    template <class RenderT>
    InternalRender<RenderT>::InternalRender(RenderT & render):
        render(render)
    {
    }

    template <class RenderT>
    sgf_core::RenderContext & InternalRender<RenderT>::RenderContext() {
        return render.RenderContext();
    }

    template <class RenderT>
    const sgf_core::RenderContext & InternalRender<RenderT>::RenderContext() const {
        return render.RenderContext();
    }
    
    template <class RenderT>
    Shader InternalRender<RenderT>::createShader(const sgf_core::ShaderId & shaderId) {
        return render.createShader(shaderId);
    }

    template <class RenderT>
    Material InternalRender<RenderT>::createMaterial(const sgf_core::MaterialId & materialId) {
        return render.createMaterial(materialId);
    }

    template <class RenderT>
    Uniform InternalRender<RenderT>::createUniform(const sgf_core::UniformId & uniformId) {
        if (std::is_const_v<RenderT>) {
            throw std::exception();
        }
        return render.createUniform(uniformId);
    }
}
