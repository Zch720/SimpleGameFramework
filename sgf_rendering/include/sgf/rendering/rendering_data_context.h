#pragma once

#include "sgf/rendering/manager/shader_manager.h"

namespace sgf::rendering {
    class RenderingDataContext {
    protected:
        ShaderManager m_oShaderManager;

    public:
        inline ShaderManager& getShaders() {
            return m_oShaderManager;
        }

        inline const ShaderManager& getShaders() const {
            return m_oShaderManager;
        }
    };
}
