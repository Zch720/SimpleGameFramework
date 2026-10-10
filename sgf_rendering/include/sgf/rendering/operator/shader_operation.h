#pragma once

#include "sgf/rendering/data/shader.h"
#include "sgf/rendering/data/shader_id.h"

namespace sgf::rendering {
    class ShaderOperation {
    public:
        virtual ~ShaderOperation() = default;

        virtual void create(const ShaderId& rId, const Shader& rShader) = 0;
        virtual void destroy(const ShaderId& rId, const Shader& rShader) = 0;

        virtual void bind(const ShaderId& rId, const Shader& rShader) = 0;
    };
}
