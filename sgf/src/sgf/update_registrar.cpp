#include "sgf/update_registrar.h"
#include <stdexcept>
#include <unordered_map>
#include <sgf/control/update_pipeline.h>

namespace sgf {
    struct UpdateRegistrar::Impl {
        sgf_core::UpdatePipeline pipeline;
        std::unordered_map<UpdateHandle, sgf_core::UpdateId> preUpdateHandles;
        std::unordered_map<UpdateHandle, sgf_core::UpdateId> updateHandles;
        std::unordered_map<UpdateHandle, sgf_core::UpdateId> postUpdateHandles;
    };

    UpdateRegistrar::UpdateRegistrar():
        handleCounter(1)
    {
        impl = std::make_unique<Impl>();
    }

    UpdateRegistrar::~UpdateRegistrar() {
    }

    UpdateRegistrar::UpdateHandle UpdateRegistrar::onPreUpdate(const UpdateFunc & func) {
        UpdateHandle handle = handleCounter++;
        sgf_core::UpdateId id = impl->pipeline.addPreUpdateFunc(func);
        impl->preUpdateHandles.emplace(handle, id);
        return handle;
    }

    UpdateRegistrar::UpdateHandle UpdateRegistrar::onUpdate(const UpdateFunc & func) {
        UpdateHandle handle = handleCounter++;
        sgf_core::UpdateId id = impl->pipeline.addUpdateFunc(func);
        impl->updateHandles.emplace(handle, id);
        return handle;
    }

    UpdateRegistrar::UpdateHandle UpdateRegistrar::onPostUpdate(const UpdateFunc & func) {
        UpdateHandle handle = handleCounter++;
        sgf_core::UpdateId id = impl->pipeline.addPostUpdateFunc(func);
        impl->postUpdateHandles.emplace(handle, id);
        return handle;
    }
    
    void UpdateRegistrar::removePreUpdate(UpdateHandle handle) {
        if (impl->preUpdateHandles.find(handle) == impl->preUpdateHandles.end()) {
            throw std::runtime_error("Try to remove pre-update function with handle " + std::to_string(handle) + ", but handle not exist");
        }
        impl->pipeline.removePreUpdateFunc(impl->preUpdateHandles.at(handle));
        impl->preUpdateHandles.erase(handle);
    }
    
    void UpdateRegistrar::removeUpdate(UpdateHandle handle) {
        if (impl->updateHandles.find(handle) == impl->updateHandles.end()) {
            throw std::runtime_error("Try to remove update function with handle " + std::to_string(handle) + ", but handle not exist");
        }
        impl->pipeline.removeUpdateFunc(impl->updateHandles.at(handle));
        impl->updateHandles.erase(handle);
    }
    
    void UpdateRegistrar::removePostUpdate(UpdateHandle handle) {
        if (impl->postUpdateHandles.find(handle) == impl->postUpdateHandles.end()) {
            throw std::runtime_error("Try to remove post-update function with handle " + std::to_string(handle) + ", but handle not exist");
        }
        impl->pipeline.removePostUpdateFunc(impl->postUpdateHandles.at(handle));
        impl->postUpdateHandles.erase(handle);
    }

    void UpdateRegistrar::preUpdate() const {
        impl->pipeline.preUpdate();
    }

    void UpdateRegistrar::update() const {
        impl->pipeline.update();
    }

    void UpdateRegistrar::postUpdate() const {
        impl->pipeline.postUpdate();
    }
}
