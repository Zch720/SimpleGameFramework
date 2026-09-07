#pragma once

#include <functional>
#include <memory>
#include <string>

namespace sgf {
    class GameLoopContext;

    class RenderRegistrar {
    public:
        using LayerHandle = uint64_t;
        using RenderHandle = uint64_t;
        using RenderFunc = std::function<void()>;

        const RenderHandle DefaultLayerHandle = 0;
        const RenderHandle DefaultRenderHandle = 0;

    private:
        friend GameLoopContext;

        struct Impl;

        std::unique_ptr<Impl> impl;

        LayerHandle layerHandleCounter;
        RenderHandle renderHandleCounter;

        void preRender() const;
        void render() const;
        void postRender() const;

    public:
        RenderRegistrar();
        ~RenderRegistrar();

        LayerHandle addLayer(const std::string & layerName, int order);

        int getLayerOrder(const std::string & layerName) const;
        int getLayerOrder(LayerHandle layerHandle) const;
        void setLayerOrder(const std::string & layerName, int order);
        void setLayerOrder(LayerHandle layerHandle, int order);

        RenderHandle onPreRender(const RenderFunc & func);
        RenderHandle onRender(const std::string & layerName , const RenderFunc & func);
        RenderHandle onRender(LayerHandle layerHandle, const RenderFunc & func);
        RenderHandle onPostRender(const RenderFunc & func);

        void changeRenderFuncLayer(RenderHandle renderHandle, const std::string & layerName);
        void changeRenderFuncLayer(RenderHandle renderHandle, LayerHandle layerHandle);

        void removePreRender(RenderHandle renderHandle);
        void removeRender(RenderHandle renderHandle);
        void removePostRender(RenderHandle renderHandle);
    };
}
