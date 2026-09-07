#pragma once

#include <functional>
#include <unordered_map>
#include <sgf/utils/id_generator.h>
#include "./command_id.h"

namespace sgf_core {
    class UpdatePipeline {
    public:
        using UpdateFunc = std::function<void()>;

    private:
        sgf_core::IdGenerator<UpdateId> idGenerator;

        std::unordered_map<UpdateId, UpdateFunc> preUpdates;
        std::unordered_map<UpdateId, UpdateFunc> updates;
        std::unordered_map<UpdateId, UpdateFunc> postUpdates;

    public:
        UpdateId addPreUpdateFunc(const UpdateFunc & func);
        UpdateId addUpdateFunc(const UpdateFunc & func);
        UpdateId addPostUpdateFunc(const UpdateFunc & func);

        void removePreUpdateFunc(const UpdateId & id);
        void removeUpdateFunc(const UpdateId & id);
        void removePostUpdateFunc(const UpdateId & id);

        void preUpdate() const;
        void update() const;
        void postUpdate() const;
    };
}
