#include "sgf/rendering/operator/adapter/shader_operation_adapter.h"

namespace sgf::rendering {
    ShaderOperationAdapter::~ShaderOperationAdapter() {
        destroyAll();
    }

    void ShaderOperationAdapter::create(
        const ShaderId &rShaderId
    ) {
        m_rOperationProvider
            .shaderOperation()
            .create(
                rShaderId,
                m_rDataContext.getShaders().getRef(rShaderId)
            );
    }
    
    void ShaderOperationAdapter::destroy(
        const ShaderId &rShaderId
    ) {
        m_rOperationProvider
            .shaderOperation()
            .destroy(
                rShaderId,
                m_rDataContext.getShaders().getRef(rShaderId)
            );
    }

    void ShaderOperationAdapter::destroyAll() {
        m_rDataContext
            .getShaders()
            .forEach([this](const ShaderId& rId, Shader& rShader) {
                m_rOperationProvider
                    .shaderOperation()
                    .destroy(rId, rShader);
            });
    }
    
    void ShaderOperationAdapter::bind(
        const ShaderId &rShaderId
    ) {
        m_rOperationProvider
            .shaderOperation()
            .bind(
                rShaderId,
                m_rDataContext.getShaders().getRef(rShaderId)
            );
    }
}
