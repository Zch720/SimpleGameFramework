#include "sgf/scene.h"

namespace sgf {
    Scene::Scene(const sgf::Camera & camera):
        camera(camera)
    {
    }

    sgf::Camera & Scene::Camera() {
        return camera;
    }

    const sgf::Camera & Scene::Camera() const {
        return camera;
    }

    UpdateRegistrar & Scene::Update() {
        return updateRegistrar;
    }

    RenderRegistrar & Scene::Render() {
        return renderRegistrar;
    }
}
