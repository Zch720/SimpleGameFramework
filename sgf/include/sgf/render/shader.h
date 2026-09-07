#pragma once

#include <memory>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"

namespace sgf {
    class Render;
    class TextRender;

    class Shader {
    public:
        using Contexts = sgf::Contexts<Render>;

    private:
        friend Render;
        friend TextRender;

        struct Impl;

        std::shared_ptr<Impl> impl;

        Contexts contexts;

        Shader(const Contexts & contexts, const sgf_core::ShaderId & shaderId);
        Shader(const Contexts & contexts, const std::string & vertexShader, const std::string & fragmentShader);

        sgf_core::ShaderId getShaderId() const;

    public:
        ~Shader();
    };
}
