#include "../../../include/sgf/control/update_pipeline.h"
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>

namespace sgf_core {
    std::string UpdateTag::TypeName = "Update";

    UpdateId UpdatePipeline::addPreUpdateFunc(const UpdateFunc & func) {
        UpdateId id = idGenerator.getNewId();
        preUpdates.emplace(id, func);
        return id;
    }

    UpdateId UpdatePipeline::addUpdateFunc(const UpdateFunc & func) {
        UpdateId id = idGenerator.getNewId();
        updates.emplace(id, func);
        return id;
    }

    UpdateId UpdatePipeline::addPostUpdateFunc(const UpdateFunc & func) {
        UpdateId id = idGenerator.getNewId();
        postUpdates.emplace(id, func);
        return id;
    }

    void UpdatePipeline::removePreUpdateFunc(const UpdateId & id) {
        if (preUpdates.find(id) == preUpdates.end()) {
            SGF_LOG_ERROR("Try to remove pre-update function with id {}, but not found.", id.toString());
            throw ResourceNotFound("Try to remove pre-update function with id " + id.toString() + ", but not found.");
        }
        preUpdates.erase(id);
        idGenerator.removeId(id);
    }

    void UpdatePipeline::removeUpdateFunc(const UpdateId & id) {
        if (updates.find(id) == updates.end()) {
            SGF_LOG_ERROR("Try to remove update function with id {}, but not found.", id.toString());
            throw ResourceNotFound("Try to remove update function with id " + id.toString() + ", but not found.");
        }
        updates.erase(id);
        idGenerator.removeId(id);
    }

    void UpdatePipeline::removePostUpdateFunc(const UpdateId & id) {
        if (postUpdates.find(id) == postUpdates.end()) {
            SGF_LOG_ERROR("Try to remove post-update function with id {}, but not found.", id.toString());
            throw ResourceNotFound("Try to remove post-update function with id " + id.toString() + ", but not found.");
        }
        postUpdates.erase(id);
        idGenerator.removeId(id);
    }

    void UpdatePipeline::preUpdate() const {
        for (const auto & [id, func] : preUpdates) {
            func();
        }
    }
    
    void UpdatePipeline::update() const {
        for (const auto & [id, func] : updates) {
            func();
        }
    }
    
    void UpdatePipeline::postUpdate() const {
        for (const auto & [id, func] : postUpdates) {
            func();
        }
    }
}
