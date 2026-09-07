#pragma once

#include "./camera.h"
#include "./render_registrar.h"
#include "./update_registrar.h"

namespace sgf {
    class GameLoopContext;

    class Scene {
    public:
        using SceneHandle = uint64_t;

        const SceneHandle DefaultSceneHandle = 0;

    private:
        friend GameLoopContext;

        sgf::Camera camera;
        
        UpdateRegistrar updateRegistrar;
        RenderRegistrar renderRegistrar;

        Scene(const sgf::Camera & camera);

    public:
        sgf::Camera & Camera();
        const sgf::Camera & Camera() const;

        UpdateRegistrar & Update();
        RenderRegistrar & Render();
    };
}
