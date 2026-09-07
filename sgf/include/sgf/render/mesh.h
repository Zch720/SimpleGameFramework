#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"

namespace sgf {
    class Render;

    class Mesh {
    public:
        using Contexts = sgf::Contexts<Render>;

    private:
        friend Render;

        struct Impl;

        std::shared_ptr<Impl> impl;

        Contexts contexts;

        Mesh(const Contexts & contexts, const std::vector<uint8_t> & vertices, const std::vector<uint32_t> & indices, const sgf_core::VertexLayout & vertexLayout);

        sgf_core::MeshId getMeshId() const;

    public:
        ~Mesh();
    };
}
