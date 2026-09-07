#include "../../../include/sgf/control/render_pipeline.h"
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>

namespace sgf_core {
    std::string RenderTag::TypeName = "Render";
    std::string RenderLayerTag::TypeName = "RenderLayer";

    RenderPipeline::RenderPipeline():
        orderDirty(false)
    {
    }

    RenderId RenderPipeline::addPreRenderFunc(const RenderFunc & func) {
        RenderId id = renderIdGenerator.getNewId();
        preRenders.emplace(id, func);
        return id;
    }

    RenderId RenderPipeline::addPostRenderFunc(const RenderFunc & func) {
        RenderId id = renderIdGenerator.getNewId();
        postRenders.emplace(id, func);
        return id;
    }

    void RenderPipeline::removePreRenderFunc(const RenderId & renderId) {
        if (preRenders.find(renderId) == preRenders.end()) {
            SGF_LOG_ERROR("Try to remove pre-render function with id {}, but not found.", renderId.toString());
            throw ResourceNotFound("Try to remove pre-render function with id " + renderId.toString() + ", but not found.");
        }
        preRenders.erase(renderId);
        renderIdGenerator.removeId(renderId);
    }

    void RenderPipeline::removePostRenderFunc(const RenderId & renderId) {
        if (postRenders.find(renderId) == postRenders.end()) {
            SGF_LOG_ERROR("Try to remove post-render function with id {}, but not found.", renderId.toString());
            throw ResourceNotFound("Try to remove post-render function with id " + renderId.toString() + ", but not found.");
        }
        postRenders.erase(renderId);
        renderIdGenerator.removeId(renderId);
    }

    RenderLayerId RenderPipeline::addLayer(int order) {
        RenderLayerId id = layerIdGenerator.getNewId();
        renderLayers.emplace(id, order);
        renderOrder.push_back(id);
        orderDirty = true;
        return id;
    }

    void RenderPipeline::removeLayer(const RenderLayerId & layerId) {
        if (renderLayers.find(layerId) == renderLayers.end()) {
            SGF_LOG_ERROR("Try to remove render layer with id {}, but not found.", layerId.toString());
            throw ResourceNotFound("Try to remove render layer with id " + layerId.toString() + ", but not found.");
        }

        auto it = std::find(renderOrder.begin(), renderOrder.end(), layerId);
        if (it != renderOrder.end()) {
            renderOrder.erase(it);
        }

        for (const RenderId & renderId : renderLayers.at(layerId).getRenderIds()) {
            renderFuncsLayer.erase(renderId);
            renderIdGenerator.removeId(renderId);
        }

        renderLayers.erase(layerId);
        layerIdGenerator.removeId(layerId);
    }

    int RenderPipeline::getLayerOrder(const RenderLayerId & layerId) const {
        if (renderLayers.find(layerId) == renderLayers.end()) {
            SGF_LOG_ERROR("Try to get render layer order with id {}, but layer not found.", layerId.toString());
            throw ResourceNotFound("Try to get render layer order with id " + layerId.toString() + ", but layer not found.");
        }
        return renderLayers.at(layerId).getOrder();
    }

    void RenderPipeline::setLayerOrder(const RenderLayerId & layerId, int order) {
        if (renderLayers.find(layerId) == renderLayers.end()) {
            SGF_LOG_ERROR("Try to set render layer order with id {}, but layer not found.", layerId.toString());
            throw ResourceNotFound("Try to set render layer order with id " + layerId.toString() + ", but layer not found.");
        }
        renderLayers.at(layerId).setOrder(order);
        orderDirty = true;
    }

    RenderId RenderPipeline::addRenderFunc(const RenderLayerId & layerId, const RenderFunc & func) {
        if (renderLayers.find(layerId) == renderLayers.end()) {
            SGF_LOG_ERROR("Try to add render function to render layer order with id {}, but layer not found.", layerId.toString());
            throw ResourceNotFound("Try to add render function to render layer order with id " + layerId.toString() + ", but layer not found.");
        }
        RenderId id = renderIdGenerator.getNewId();
        renderLayers.at(layerId).addRenderFunc(id, func);
        renderFuncsLayer.emplace(id, layerId);
        return id;
    }

    void RenderPipeline::changeRenderFuncLayer(const RenderId & renderId, const RenderLayerId & layerId) {
        if (renderLayers.find(layerId) == renderLayers.end()) {
            SGF_LOG_ERROR("Try to change render function layer with id {}, but layer not found.", layerId.toString());
            throw ResourceNotFound("Try to add render function layer with id " + layerId.toString() + ", but layer not found.");
        }
        RenderLayer & oldLayer = renderLayers.at(renderFuncsLayer.at(renderId));
        renderLayers.at(layerId).addRenderFunc(renderId, oldLayer.getFunc(renderId));
        oldLayer.removeRenderFunc(renderId);
        renderFuncsLayer.at(renderId) = layerId;
    }

    void RenderPipeline::removeRenderFunc(const RenderId & renderId) {
        if (renderFuncsLayer.find(renderId) == renderFuncsLayer.end()) {
            SGF_LOG_ERROR("Try to remove render function with id {}, but it's layer not found.", renderId.toString());
            throw ResourceNotFound("Try to remove render function with id " + renderId.toString() + ", but it's layer not found.");
        }
        RenderLayerId layerId = renderFuncsLayer.at(renderId); 
        if (renderLayers.find(layerId) == renderLayers.end()) {
            SGF_LOG_ERROR("Try to get render layer with id {}, but layer not found.", layerId.toString());
            throw ResourceNotFound("Try to get render layer with id " + layerId.toString() + ", but layer not found.");
        }
        renderLayers.at(layerId).removeRenderFunc(renderId);
        renderFuncsLayer.erase(renderId);
        renderIdGenerator.removeId(renderId);
    }

    void RenderPipeline::sortRender() {
        if (orderDirty) {
            std::sort(renderOrder.begin(), renderOrder.end(),
                [this](const RenderLayerId & id1, const RenderLayerId & id2) {
                    return renderLayers.at(id1).getOrder() < renderLayers.at(id2).getOrder();
                });
        }
    }

    void RenderPipeline::preRender() const {
        for (const auto & [id, func] : preRenders) {
            func();
        }
    }

    void RenderPipeline::render() const {
        for (const auto & id : renderOrder) {
            renderLayers.at(id).render();
        }
    }

    void RenderPipeline::postRender() const {
        for (const auto & [id, func] : postRenders) {
            func();
        }
    }



    RenderPipeline::RenderLayer::RenderLayer(int order):
        order(order)
    {
    }

    int RenderPipeline::RenderLayer::getOrder() const {
        return order;
    }
    
    void RenderPipeline::RenderLayer::setOrder(int order) {
        this->order = order;
    }

    void RenderPipeline::RenderLayer::addRenderFunc(const RenderId & id, const RenderFunc & func) {
        renders.emplace(id, func);
    }

    void RenderPipeline::RenderLayer::removeRenderFunc(const RenderId & id) {
        if (renders.find(id) == renders.end()) {
            SGF_LOG_ERROR("Try to remove render function with id {}, but not found.", id.toString());
            throw ResourceNotFound("Try to remove render function with id " + id.toString() + ", but not found.");
        }
        renders.erase(id);
    }

    void RenderPipeline::RenderLayer::render() const {
        for (const auto & [id, func] : renders) {
            func();
        }
    }

    std::vector<RenderId> RenderPipeline::RenderLayer::getRenderIds() const {
        std::vector<RenderId> ids;
        for (const auto & [id, func] : renders) {
            ids.push_back(id);
        }
        return ids;
    }

    const RenderPipeline::RenderFunc & RenderPipeline::RenderLayer::getFunc(const RenderId & id) const {
        if (renders.find(id) == renders.end()) {
            SGF_LOG_ERROR("Try to get render function with id {}, but not found.", id.toString());
            throw ResourceNotFound("Try to get render function with id " + id.toString() + ", but not found.");
        }
        return renders.at(id);
    }
}
