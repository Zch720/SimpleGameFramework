#pragma once

#include "sgf/rendering/rendering_data_context.h"
#include "sgf/rendering/data/shader_id.h"
#include "sgf/rendering/operator/rendering_operation_provider.h"

namespace sgf::rendering {
    class ShaderOperationAdapter {
    private:
        RenderingDataContext& m_rDataContext;
        RenderingOperationProvider& m_rOperationProvider;
    
    public:
        ShaderOperationAdapter(
            RenderingDataContext& rDataContext,
            RenderingOperationProvider& rOperationProvider
        ):
            m_rDataContext(rDataContext),
            m_rOperationProvider(rOperationProvider)
        {
        }

        ~ShaderOperationAdapter();

        void create(const ShaderId& rShaderId);
        void destroy(const ShaderId& rShaderId);
        void destroyAll();

        void bind(const ShaderId& rShaderId);
    };
}
