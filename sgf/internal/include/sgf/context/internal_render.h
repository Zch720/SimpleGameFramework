#pragma once

#include "sgf/context/render.h"

namespace sgf {
    template <class RenderT>
    class InternalRender {
        static_assert(std::is_same_v<RenderT, sgf::Render> || std::is_same_v<RenderT, const sgf::Render>,
            "Generic type of InternalRender must be Render or const Render");

    private:
        RenderT & render;

    public:
        InternalRender(RenderT & render);
        
        sgf_core::RenderContext & RenderContext();
        const sgf_core::RenderContext & RenderContext() const;

        Shader createShader(const sgf_core::ShaderId & shaderId);
        Material createMaterial(const sgf_core::MaterialId & materialId);
        Uniform createUniform(const sgf_core::UniformId & uniformId);
    };
}

#include "../../../templte_src/sgf/context/internal_render.tpp"
