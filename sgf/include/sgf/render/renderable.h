#pragma once

#include <memory>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"
#include "sgf/transform.h"

namespace sgf {
    class Render;

    class Renderable {
    public:
        using Contexts = sgf::Contexts<Render>;

    private:
        friend Render;

        struct Impl;

        std::shared_ptr<Impl> impl;

        Contexts contexts;
        
        sgf::Transform transform;

        Renderable(const Contexts & contexts, const sgf_core::MeshId & meshId, const sgf_core::MaterialId & materialId);

        sgf_core::RenderableId getRenderableId() const;

    public:
        ~Renderable();

        sgf::Transform & Transform();
        const sgf::Transform & Transform() const;

        void update();
        void render();
    };
}
