#pragma once

#include "sgf/rendering/rendering_data_context.h"
#include "sgf/rendering/operator/rendering_operation_provider.h"
#include "sgf/rendering/operator/adapter/shader_operation_adapter.h"

namespace sgf::rendering {
    class RenderingOperateContext {
    private:
        RenderingDataContext& m_rDataContext;
        RenderingOperationProvider& m_rOperationProvider;
        
        ShaderOperationAdapter m_oShaderOperateAdapter;

    public:
        RenderingOperateContext(
            RenderingDataContext& rDataContext,
            RenderingOperationProvider& rOperationProvider
        ):
            m_rDataContext(rDataContext),
            m_rOperationProvider(rOperationProvider),
            m_oShaderOperateAdapter(rDataContext, rOperationProvider)
        {
        }

        virtual ~RenderingOperateContext() {
        }

        ShaderOperationAdapter& shaderOperate() {
            return m_oShaderOperateAdapter;
        }
    };
}
