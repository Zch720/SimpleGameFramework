#pragma once

#include <functional>
#include <memory>

namespace sgf {
    class GameLoopContext;

    class UpdateRegistrar {
    public:
        using UpdateHandle = uint64_t;
        using UpdateFunc = std::function<void()>;

        const UpdateHandle DefaultUpdateHandle = 0;

    private:
        friend GameLoopContext;

        struct Impl;
        
        std::unique_ptr<Impl> impl;
        
        UpdateHandle handleCounter;

        void preUpdate() const;
        void update() const;
        void postUpdate() const;

    public:
        UpdateRegistrar();
        ~UpdateRegistrar();

        UpdateHandle onPreUpdate(const UpdateFunc & func);
        UpdateHandle onUpdate(const UpdateFunc & func);
        UpdateHandle onPostUpdate(const UpdateFunc & func);
        
        void removePreUpdate(UpdateHandle handle);
        void removeUpdate(UpdateHandle handle);
        void removePostUpdate(UpdateHandle handle);
    };
}
