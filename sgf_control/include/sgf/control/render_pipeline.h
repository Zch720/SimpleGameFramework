#pragma once

#include <functional>
#include <unordered_map>
#include <sgf/utils/id_generator.h>
#include "./command_id.h"
#include "./render_layer_id.h"

namespace sgf_core {
    class RenderPipeline {
    public:
        using RenderFunc = std::function<void()>;

    private:
        class RenderLayer {
        private:
            friend RenderPipeline;

            int order;

            std::unordered_map<RenderId, RenderFunc> renders;

            std::vector<RenderId> getRenderIds() const;
            const RenderFunc & getFunc(const RenderId & id) const;
            
        public:
            RenderLayer(int order);

            int getOrder() const;
            void setOrder(int order);

            void addRenderFunc(const RenderId & id, const RenderFunc & func);
            void removeRenderFunc(const RenderId & id);

            void render() const;
        };

        sgf_core::IdGenerator<RenderId> renderIdGenerator;
        sgf_core::IdGenerator<RenderLayerId> layerIdGenerator;

        std::unordered_map<RenderId, RenderFunc> preRenders;
        std::unordered_map<RenderId, RenderFunc> postRenders;

        bool orderDirty;
        std::vector<RenderLayerId> renderOrder;
        std::unordered_map<RenderLayerId, RenderLayer> renderLayers;
        std::unordered_map<RenderId, RenderLayerId> renderFuncsLayer;

    public:
        RenderPipeline();

        RenderId addPreRenderFunc(const RenderFunc & func);
        RenderId addPostRenderFunc(const RenderFunc & func);

        void removePreRenderFunc(const RenderId & renderId);
        void removePostRenderFunc(const RenderId & renderId);

        RenderLayerId addLayer(int order);
        void removeLayer(const RenderLayerId & layerId);

        int getLayerOrder(const RenderLayerId & layerId) const;
        void setLayerOrder(const RenderLayerId & layerId, int order);

        RenderId addRenderFunc(const RenderLayerId & layerId, const RenderFunc & func);
        void changeRenderFuncLayer(const RenderId & renderId, const RenderLayerId & layerId);
        void removeRenderFunc(const RenderId & renderId);

        void sortRender();

        void preRender() const;
        void render() const;
        void postRender() const;
    };
}
