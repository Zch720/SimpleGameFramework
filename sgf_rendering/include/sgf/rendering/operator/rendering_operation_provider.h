#pragma once

#include "sgf/rendering/operator/shader_operation.h"

namespace sgf::rendering {
    class RenderingOperationProvider {
    public:
        ~RenderingOperationProvider() {}

        virtual ShaderOperation& shaderOperation() = 0;
    };
}
