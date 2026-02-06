#include "../../../include/sgf/rendering/render_context.h"
#include "sgf/rendering/camera.h"
#include "sgf/rendering/uniform_provider.h"
#include <glad/gl.h>

namespace sgf_core {
    RenderContext::RenderContext(): clearFrameBufferBits(0) {
    }

    void RenderContext::initialize() {
        glEnable(GL_DEPTH_TEST);

        clearFrameBufferBits |= GL_DEPTH_BUFFER_BIT;
    }

    void RenderContext::destroyAllResources() {
        shaderManager.destroyAll();
        texture2DManager.destroyAll();
        meshManager.destroyAll();
        materialManager.destroyAll();
        renderableManager.destroyAll();
    }

    sgf_core::ShaderManager & RenderContext::ShaderManager() {
        return shaderManager;
    }

    const sgf_core::ShaderManager & RenderContext::ShaderManager() const {
        return shaderManager;
    }

    sgf_core::Texture2DManager & RenderContext::Texture2DManager() {
        return texture2DManager;
    }

    const sgf_core::Texture2DManager & RenderContext::Texture2DManager() const {
        return texture2DManager;
    }

    sgf_core::MeshManager & RenderContext::MeshManager() {
        return meshManager;
    }

    const sgf_core::MeshManager & RenderContext::MeshManager() const {
        return meshManager;
    }

    sgf_core::MaterialManager & RenderContext::MaterialManager() {
        return materialManager;
    }

    const sgf_core::MaterialManager & RenderContext::MaterialManager() const {
        return materialManager;
    }

    sgf_core::RenderableManager & RenderContext::RenderableManager() {
        return renderableManager;
    }

    const sgf_core::RenderableManager & RenderContext::RenderableManager() const {
        return renderableManager;
    }

    uint32_t RenderContext::getClearFrameBufferBits() const {
        return clearFrameBufferBits;
    }

    sgf_core::Camera & RenderContext::Camera() {
        return camera;
    }

    const sgf_core::Camera & RenderContext::Camera() const {
        return camera;
    }

    sgf_core::UniformProvider & RenderContext::UniformProvider() {
        return uniformProvider;
    }

    const sgf_core::UniformProvider & RenderContext::UniformProvider() const {
        return uniformProvider;
    }
}
