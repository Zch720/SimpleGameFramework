#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "sgf/context/render.h"
#include "sgf/contexts.h"
#include "sgf/game_frame_phase.h"
#include "sgf/render_registrar.h"
#include "sgf/scene.h"
#include "sgf/time.h"
#include "sgf/ui.h"
#include "sgf/update_registrar.h"

namespace sgf_core {
    class GameRuntime;
    class PlatformContext;
    class RenderContext;
}

namespace sgf_font {
    class FontRenderContext;
}

namespace sgf {
    class Game;

    class GameLoopContext {
    public:
        using Contexts = sgf::Contexts<
            sgf::Render,
            sgf_core::PlatformContext
        >;
    
    private:
        friend Game;

        Contexts contexts;

        std::unique_ptr<sgf_core::GameRuntime> gameRuntime;
    
        FramePhase currentPhase;
        sgf::UI ui;
        sgf::Time time;

        Camera camera;

        Scene::SceneHandle currentScene;
        Scene::SceneHandle sceneHandleCounter;
        std::unordered_map<std::string, Scene::SceneHandle> sceneNames;
        std::unordered_map<Scene::SceneHandle, std::unique_ptr<Scene>> scenes;

        void beginFrame();
        void preUpdate();
        void update();
        void postUpdate();
        void preRender();
        void render();
        void postRender();
        void endFrame();

        GameLoopContext(const Contexts & contexts, const Camera & camera);

    public:
        GameLoopContext(const GameLoopContext &) = delete;
        GameLoopContext & operator=(const GameLoopContext &) = delete;
        ~GameLoopContext();

        bool isRunning() const;
        FramePhase getCurrentPhase() const;

        sgf::Render & Render();
        const sgf::Render & Render() const;

        sgf::Time & Time();
        const sgf::Time & Time() const;
        
        sgf::UI & UI();
        const sgf::UI & UI() const;

        Scene::SceneHandle createScene(const std::string & sceneName);
        
        void switchScene(const std::string & sceneName);
        void switchScene(Scene::SceneHandle sceneHandle);

        Scene & getCurrentSceneRef();
        const Scene & getCurrentSceneRef() const;

        void run();
        void stop();
    };
}
