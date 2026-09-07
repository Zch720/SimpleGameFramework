#include "sgf/render/shader.h"
#include <sgf/rendering/render_context.h>
#include "sgf/context/render.h"
#include "sgf/context/internal_render.h"

namespace sgf {
    struct Shader::Impl {
        sgf_core::ShaderId shaderId;
    };

    Shader::Shader(const Contexts & contexts, const sgf_core::ShaderId & shaderId):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->shaderId = shaderId;
    }

    Shader::Shader(const Contexts & contexts, const std::string & vertexShader, const std::string & fragmentShader):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->shaderId = InternalRender(this->contexts.get<Render>())
            .RenderContext()
            .ShaderManager()
            .create({
                .vertexShaderSource = vertexShader,
                .fragmentShaderSource = fragmentShader
            });
    }

    Shader::~Shader() {
    }

    sgf_core::ShaderId Shader::getShaderId() const {
        return impl->shaderId;
    }
}
