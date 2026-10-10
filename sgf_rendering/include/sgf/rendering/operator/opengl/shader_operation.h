#pragma once

#include <unordered_map>

#include "sgf/rendering/operator/shader_operation.h"
#include "sgf/utils/manager/resource_id.h"

namespace sgf::rendering {
    class ShaderOperationOpenGL final: public ShaderOperation {
    private:
        using HandleMap =
            std::unordered_map<
                ShaderId,
                uint32_t,
                sgf::utils::ResourceIdHasher<ShaderId>,
                sgf::utils::ResourceIdEqual<ShaderId>
            >;
        
        HandleMap m_mapShaderProgramHandles;

        HandleMap::iterator getHandle(const ShaderId& rId, bool bThrowWhenNotFound = true);

    public:
        void create(const ShaderId& rId, const Shader& rShader) override;
        void destroy(const ShaderId& rId, const Shader& rShader) override;

        void bind(const ShaderId& rId, const Shader& rShader) override;
    };
}
