#include "sgf/render_registrar.h"
#include <unordered_map>
#include <sgf/control/render_pipeline.h>
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>

namespace sgf {
    struct RenderRegistrar::Impl {
        sgf_core::RenderPipeline pipeline;
        std::unordered_map<RenderHandle, sgf_core::RenderId> preRenderHandles;
        std::unordered_map<RenderHandle, sgf_core::RenderId> postRenderHandles;

        std::unordered_map<std::string, sgf_core::RenderLayerId> layerNames;
        std::unordered_map<LayerHandle, sgf_core::RenderLayerId> layerHandles;
        std::unordered_map<RenderHandle, sgf_core::RenderId> renderHandles;
    };

    RenderRegistrar::RenderRegistrar():
        layerHandleCounter(1),
        renderHandleCounter(1)
    {
        impl = std::make_unique<Impl>();
    }

    RenderRegistrar::~RenderRegistrar() {
    }

    RenderRegistrar::LayerHandle RenderRegistrar::addLayer(const std::string & layerName, int order) {
        LayerHandle handle = layerHandleCounter++;
        sgf_core::RenderLayerId id = impl->pipeline.addLayer(order);
        impl->layerNames.emplace(layerName, id);
        impl->layerHandles.emplace(handle, id);
        return handle;
    }

    int RenderRegistrar::getLayerOrder(const std::string & layerName) const {
        if (impl->layerNames.find(layerName) == impl->layerNames.end()) {
            SGF_LOG_ERROR("Try to get layer order with layer name {}, but layer not found.", layerName);
            throw sgf_core::ResourceNotFound("Try to get layer order with layer name " + layerName + ", but layer not found.");
        }
        return impl->pipeline.getLayerOrder(impl->layerNames.at(layerName));
    }

    int RenderRegistrar::getLayerOrder(LayerHandle layerHandle) const {
        if (impl->layerHandles.find(layerHandle) == impl->layerHandles.end()) {
            SGF_LOG_ERROR("Try to get layer order with handle {}, but layer not found.", layerHandle);
            throw sgf_core::ResourceNotFound("Try to get layer order with handle " + std::to_string(layerHandle) + ", but layer not found.");
        }
        return impl->pipeline.getLayerOrder(impl->layerHandles.at(layerHandle));
    }

    void RenderRegistrar::setLayerOrder(const std::string & layerName, int order) {
        if (impl->layerNames.find(layerName) == impl->layerNames.end()) {
            SGF_LOG_ERROR("Try to set layer order with layer name {}, but layer not found.", layerName);
            throw sgf_core::ResourceNotFound("Try to set layer order with layer name " + layerName + ", but layer not found.");
        }
        impl->pipeline.setLayerOrder(impl->layerNames.at(layerName), order);
    }

    void RenderRegistrar::setLayerOrder(LayerHandle layerHandle, int order) {
        if (impl->layerHandles.find(layerHandle) == impl->layerHandles.end()) {
            SGF_LOG_ERROR("Try to set layer order with handle {}, but layer not found.", layerHandle);
            throw sgf_core::ResourceNotFound("Try to set layer order with handle " + std::to_string(layerHandle) + ", but layer not found.");
        }
        impl->pipeline.setLayerOrder(impl->layerHandles.at(layerHandle), order);
    }

    RenderRegistrar::RenderHandle RenderRegistrar::onPreRender(const RenderFunc & func) {
        RenderHandle handle = renderHandleCounter++;
        sgf_core::RenderId id = impl->pipeline.addPreRenderFunc(func);
        impl->preRenderHandles.emplace(handle, id);
        return handle;
    }
    
    RenderRegistrar::RenderHandle RenderRegistrar::onRender(const std::string & layerName, const RenderFunc & func) {
        if (impl->layerNames.find(layerName) == impl->layerNames.end()) {
            SGF_LOG_ERROR("Try to add render function to layer with layer name {}, but layer not found.", layerName);
            throw sgf_core::ResourceNotFound("Try to add render function to layer with layer name " + layerName + ", but layer not found.");
        }
        RenderHandle handle = renderHandleCounter++;
        sgf_core::RenderId id = impl->pipeline.addRenderFunc(impl->layerNames.at(layerName), func);
        impl->renderHandles.emplace(handle, id);
        return handle;
    }
    
    RenderRegistrar::RenderHandle RenderRegistrar::onRender(LayerHandle layerHandle, const RenderFunc & func) {
        if (impl->layerHandles.find(layerHandle) == impl->layerHandles.end()) {
            SGF_LOG_ERROR("Try to add render function to layer with handle {}, but layer not found.", layerHandle);
            throw sgf_core::ResourceNotFound("Try to add render function to layer with handle " + std::to_string(layerHandle) + ", but layer not found.");
        }
        RenderHandle handle = renderHandleCounter++;
        sgf_core::RenderId id = impl->pipeline.addRenderFunc(impl->layerHandles.at(layerHandle), func);
        impl->renderHandles.emplace(handle, id);
        return handle;
    }

    RenderRegistrar::RenderHandle RenderRegistrar::onPostRender(const RenderFunc & func) {
        RenderHandle handle = renderHandleCounter++;
        sgf_core::RenderId id = impl->pipeline.addPostRenderFunc(func);
        impl->postRenderHandles.emplace(handle, id);
        return handle;
    }

    void RenderRegistrar::changeRenderFuncLayer(RenderHandle renderHandle, const std::string & layerName) {
        if (impl->renderHandles.find(renderHandle) == impl->renderHandles.end()) {
            SGF_LOG_ERROR("Try to change render function to layer with render handle {}, but render function not found.", renderHandle);
            throw sgf_core::ResourceNotFound("Try to change render function to layer with render handle " + std::to_string(renderHandle) + ", but render function not found.");
        }
        if (impl->layerNames.find(layerName) == impl->layerNames.end()) {
            SGF_LOG_ERROR("Try to change render function to layer with layer name {}, but layer not found.", layerName);
            throw sgf_core::ResourceNotFound("Try to change render function to layer with layer name " + layerName + ", but layer not found.");
        }
        impl->pipeline.changeRenderFuncLayer(impl->renderHandles.at(renderHandle), impl->layerNames.at(layerName));
    }

    void RenderRegistrar::changeRenderFuncLayer(RenderHandle renderHandle, LayerHandle layerHandle) {
        if (impl->renderHandles.find(renderHandle) == impl->renderHandles.end()) {
            SGF_LOG_ERROR("Try to change render function to layer with render handle {}, but render function not found.", renderHandle);
            throw sgf_core::ResourceNotFound("Try to change render function to layer with render handle " + std::to_string(renderHandle) + ", but render function not found.");
        }
        if (impl->layerHandles.find(layerHandle) == impl->layerHandles.end()) {
            SGF_LOG_ERROR("Try to change render function to layer with handle {}, but layer not found.", layerHandle);
            throw sgf_core::ResourceNotFound("Try to change render function to layer with handle " + std::to_string(layerHandle) + ", but layer not found.");
        }
        impl->pipeline.changeRenderFuncLayer(impl->renderHandles.at(renderHandle), impl->layerHandles.at(layerHandle));
    }

    void RenderRegistrar::removePreRender(RenderHandle renderHandle) {
        if (impl->preRenderHandles.find(renderHandle) == impl->preRenderHandles.end()) {
            SGF_LOG_ERROR("Try to remove pre-render function with render handle {}, but render function not found.", renderHandle);
            throw sgf_core::ResourceNotFound("Try to remove pre-render function with render handle " + std::to_string(renderHandle) + ", but render function not found.");
        }
        impl->pipeline.removePreRenderFunc(impl->preRenderHandles.at(renderHandle));
    }

    void RenderRegistrar::removeRender(RenderHandle renderHandle) {
        if (impl->renderHandles.find(renderHandle) == impl->renderHandles.end()) {
            SGF_LOG_ERROR("Try to remove render function with render handle {}, but render function not found.", renderHandle);
            throw sgf_core::ResourceNotFound("Try to remove render function with render handle " + std::to_string(renderHandle) + ", but render function not found.");
        }
        impl->pipeline.removePreRenderFunc(impl->renderHandles.at(renderHandle));
    }

    void RenderRegistrar::removePostRender(RenderHandle renderHandle) {
        if (impl->postRenderHandles.find(renderHandle) == impl->postRenderHandles.end()) {
            SGF_LOG_ERROR("Try to remove post-render function with render handle {}, but render function not found.", renderHandle);
            throw sgf_core::ResourceNotFound("Try to remove post-render function with render handle " + std::to_string(renderHandle) + ", but render function not found.");
        }
        impl->pipeline.removePreRenderFunc(impl->postRenderHandles.at(renderHandle));
    }

    void RenderRegistrar::preRender() const {
        impl->pipeline.preRender();
    }

    void RenderRegistrar::render() const {
        impl->pipeline.render();
    }

    void RenderRegistrar::postRender() const {
        impl->pipeline.postRender();
    }
}
