#pragma once

#include <memory>
#include "sgf/camera.h"
#include "sgf/context/render.h"
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"
#include "sgf/time.h"
#include "sgf/ui.h"
#include "sgf/context/render.h"

namespace sgf {
    class Game;

    class GameContext {
    public:
        using Contexts = sgf::Contexts<
            sgf::Render,
            sgf_core::PlatformContext
        >;

    private:
        friend Game;

        Contexts contexts;

        std::unique_ptr<sgf_core::GameRuntime> gameRuntime;
        
        sgf::UI ui;
        sgf::Time time;

        sgf::Camera camera;
        
        GameContext(const Contexts & contexts, const sgf::Camera & camera);

    public:
        GameContext(const GameContext &) = delete;
        GameContext & operator=(const GameContext &) = delete;

        bool isStop() const;

        sgf::Render & Render();
        const sgf::Render & Render() const;

        sgf::Camera & Camera();
        const sgf::Camera & Camera() const;

        sgf::Time & Time();
        const sgf::Time & Time() const;

        sgf::UI & UI();
        const sgf::UI & UI() const;

        void beginFrame();
        void endFrame();

        void stop();
    };
}
