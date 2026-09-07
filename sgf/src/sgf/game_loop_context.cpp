#include "sgf/game_loop_context.h"
#include <sgf/control/game_runtime.h>
#include <sgf/utils/exceptions/resource_not_found.h>
#include "sgf/context/internal_render.h"

namespace sgf {
    GameLoopContext::GameLoopContext(const Contexts & contexts, const Camera & camera):
        currentPhase(FramePhase::BEGIN_FRAME),
        contexts(contexts),
        gameRuntime(std::make_unique<sgf_core::GameRuntime>(
            this->contexts.get<sgf_core::PlatformContext>(),
            InternalRender(this->contexts.get<sgf::Render>()).RenderContext()
        )),
        ui(this->contexts),
        time(gameRuntime->Time()),
        camera(camera),
        currentScene(0),
        sceneHandleCounter(1)
    {
        ui.setSize({
            (float)contexts.get<sgf_core::PlatformContext>().Window().getWidth(),
            (float)contexts.get<sgf_core::PlatformContext>().Window().getHeight()
        });
    }

    GameLoopContext::~GameLoopContext() {
    }

    bool GameLoopContext::isRunning() const {
        return !gameRuntime->isStop();
    }

    FramePhase GameLoopContext::getCurrentPhase() const {
        return currentPhase;
    }

    sgf::Render & GameLoopContext::Render() {
        return contexts.get<sgf::Render>();
    }

    const sgf::Render & GameLoopContext::Render() const {
        return contexts.get<sgf::Render>();
    }

    sgf::Time & GameLoopContext::Time() {
        return time;
    }

    const sgf::Time & GameLoopContext::Time() const {
        return time;
    }

    sgf::UI & GameLoopContext::UI() {
        return ui;
    }

    const sgf::UI & GameLoopContext::UI() const {
        return ui;
    }

    Scene::SceneHandle GameLoopContext::createScene(const std::string & sceneName) {
        Scene::SceneHandle handle = sceneHandleCounter++;
        sceneNames[sceneName] = handle;
        scenes.emplace(handle, std::unique_ptr<Scene>(new Scene(camera)));
        return handle;
    }

    void GameLoopContext::switchScene(const std::string & sceneName) {
        if (sceneNames.find(sceneName) == sceneNames.end()) {
            throw sgf_core::ResourceNotFound("Try to switch scene with scene name " + sceneName + ", but scene not found.");
        }
        switchScene(sceneNames[sceneName]);
    }

    void GameLoopContext::switchScene(Scene::SceneHandle sceneHandle) {
        if (scenes.find(sceneHandle) == scenes.end()) {
            throw sgf_core::ResourceNotFound("Try to switch scene with scene handle " + std::to_string(sceneHandle) + ", but scene not found.");
        }
        currentScene = sceneHandle;
    }

    Scene & GameLoopContext::getCurrentSceneRef() {
        return *scenes.at(currentScene);
    }

    const Scene & GameLoopContext::getCurrentSceneRef() const {
        return *scenes.at(currentScene);
    }

    void GameLoopContext::run() {
        while (!gameRuntime->isStop()) {
            beginFrame();
            if (gameRuntime->isStop()) break;
            preUpdate();
            update();
            postUpdate();
            if (gameRuntime->isStop()) break;
            preRender();
            render();
            postRender();
            endFrame();
        }
    }

    void GameLoopContext::stop() {
        gameRuntime->stop();
    }

    void GameLoopContext::beginFrame() {
        ((sgf_core::FrameControl *)gameRuntime.get())->beginFrame();
        currentPhase = FramePhase::BEGIN_FRAME;
    }

    void GameLoopContext::preUpdate(){
        scenes[currentScene]->updateRegistrar.preUpdate();
        currentPhase = FramePhase::PRE_UPDATE;
    }

    void GameLoopContext::update(){
        scenes[currentScene]->updateRegistrar.update();
        currentPhase = FramePhase::UPDATE;
    }

    void GameLoopContext::postUpdate(){
        scenes[currentScene]->updateRegistrar.postUpdate();
        currentPhase = FramePhase::POST_UPDATE;
    }

    void GameLoopContext::preRender(){
        scenes[currentScene]->renderRegistrar.preRender();
        currentPhase = FramePhase::PRE_RENDER;
    }

    void GameLoopContext::render(){
        scenes[currentScene]->renderRegistrar.render();
        currentPhase = FramePhase::RENDER;
    }

    void GameLoopContext::postRender(){
        scenes[currentScene]->renderRegistrar.postRender();
        currentPhase = FramePhase::POST_RENDER;
    }

    void GameLoopContext::endFrame(){
        ((sgf_core::FrameControl *)gameRuntime.get())->endFrame();
        currentPhase = FramePhase::END_FRAME;
    }

}
