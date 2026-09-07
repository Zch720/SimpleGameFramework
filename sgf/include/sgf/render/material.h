#pragma once

#include <memory>
#include <optional>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"
#include "sgf/render/uniform.h"

namespace sgf {
    class Render;
    class TextRender;

    class Material {
    public:
        using Contexts = sgf::Contexts<Render>;
    
    private:
        friend Render;
        friend TextRender;

        struct Impl;

        std::shared_ptr<Impl> impl;

        Contexts contexts;

        Material(const Contexts & contexts, const sgf_core::MaterialId & materialId);
        Material(const Contexts & contexts, const sgf_core::ShaderId & shaderId);
        Material(const Contexts & contexts, const sgf_core::ShaderId & shaderId, const sgf_core::Texture2DId & textureId);

        sgf_core::MaterialId getMaterialId() const;

    public:
        ~Material();

        bool isUsingTexture() const;
        void useTexture(bool useTexture);

        std::optional<Uniform> registerUniform(const std::string & name, UniformSource sourceType);
    };
}
