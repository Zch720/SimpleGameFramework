#pragma once

#include "sgf/rendering/data/shader.h"
#include "sgf/rendering/data/shader_id.h"
#include "sgf/utils/manager/resource_manager.h"

namespace sgf::rendering {
    class ShaderManager: public sgf::utils::ResourceManager<Shader, ShaderId> {
    public:
        ~ShaderManager();
    };
}
