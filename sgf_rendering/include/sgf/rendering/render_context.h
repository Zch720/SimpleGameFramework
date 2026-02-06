#pragma once

#include <sgf/utils/manager.h>
#include "./camera.h"
#include "./material_manager.h"
#include "./mesh_manager.h"
#include "./renderable_manager.h"
#include "./shader_manager.h"
#include "./texture_2d_manager.h"
#include "./uniform_provider.h"

#ifdef SGF_RENDERING_UNSAFE
#include "../../../unsafe/include/sgf/rendering/unsafe_gl_context.h"
#endif

namespace sgf_core {
    class RenderContext {
    public:
        RenderContext();

        sgf_core::ShaderManager & ShaderManager();
        const sgf_core::ShaderManager & ShaderManager() const;

        sgf_core::Texture2DManager & Texture2DManager();
        const sgf_core::Texture2DManager & Texture2DManager() const;

        sgf_core::MeshManager & MeshManager();
        const sgf_core::MeshManager & MeshManager() const;

        sgf_core::MaterialManager & MaterialManager();
        const sgf_core::MaterialManager & MaterialManager() const;

        sgf_core::RenderableManager & RenderableManager();
        const sgf_core::RenderableManager & RenderableManager() const;

        void initialize();
        void destroyAllResources();

        uint32_t getClearFrameBufferBits() const;

        sgf_core::Camera & Camera();
        const sgf_core::Camera & Camera() const;
        
        sgf_core::UniformProvider & UniformProvider();
        const sgf_core::UniformProvider & UniformProvider() const;

    #ifdef SGF_RENDERING_UNSAFE
        template <typename Fn>
        void unsafeExecute(Fn&& fn) {
            UnsafeGLContext glContext(*this);
            fn(glContext);
        }

        void addClearFrameBufferBit(uint32_t bit) {
            clearFrameBufferBits |= bit;
        }
    #endif

    private:
        uint32_t clearFrameBufferBits;

        sgf_core::UniformProvider uniformProvider;
        sgf_core::Camera camera;

        sgf_core::ShaderManager shaderManager;
        sgf_core::Texture2DManager texture2DManager;
        sgf_core::MeshManager meshManager;
        sgf_core::MaterialManager materialManager;
        sgf_core::RenderableManager renderableManager;
    };
}
