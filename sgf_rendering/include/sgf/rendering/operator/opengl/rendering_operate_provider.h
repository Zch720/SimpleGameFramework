#pragma once

#include "sgf/rendering/operator/opengl/shader_operation.h"
#include "sgf/rendering/operator/rendering_operation_provider.h"

namespace sgf::rendering {
    class RenderingOperateProviderOpenGL final: public RenderingOperationProvider {
    private:
        ShaderOperationOpenGL m_oShaderOperate;

    public:
        inline ShaderOperation& shaderOperation() override {
            return m_oShaderOperate;
        }
    };
}
