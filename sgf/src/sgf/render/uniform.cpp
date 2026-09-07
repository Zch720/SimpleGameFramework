#include "sgf/render/uniform.h"
#include <sgf/rendering/render_context.h>
#include <sgf/type/casting/cast_vec2.h>
#include <sgf/type/casting/cast_vec3.h>
#include <sgf/type/casting/cast_vec4.h>
#include <sgf/type/casting/cast_mat2.h>
#include <sgf/type/casting/cast_mat2x3.h>
#include <sgf/type/casting/cast_mat2x4.h>
#include <sgf/type/casting/cast_mat3.h>
#include <sgf/type/casting/cast_mat3x2.h>
#include <sgf/type/casting/cast_mat3x4.h>
#include <sgf/type/casting/cast_mat4.h>
#include <sgf/type/casting/cast_mat4x2.h>
#include <sgf/type/casting/cast_mat4x3.h>
#include <sgf/context/render.h>
#include <sgf/context/internal_render.h>
#include <variant>

namespace sgf {
    struct Uniform::Impl {
        sgf_core::UniformId uniformId;
    };

    struct SetCoreProviderVisitor {
        sgf_core::RenderContext & renderContext;
        sgf_core::UniformId uniformId;
        
        SetCoreProviderVisitor(sgf_core::RenderContext & renderContext, const sgf_core::UniformId & uniformId):
            renderContext(renderContext),
            uniformId(uniformId)
        {
        }

        void operator()(const int & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return value;
            });
        }

        void operator()(const float & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return value;
            });
        }

        void operator()(const Vec2 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Vec3 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Vec4 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat2 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat3 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat4 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat2x3 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat3x2 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat2x4 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat4x2 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat3x4 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }

        void operator()(const Mat4x3 & value) {
            renderContext.UniformProvider().setProviderFunc(uniformId, [&value]() {
                return toGlm(value);
            });
        }
    };

    Uniform::Uniform(const Contexts & contexts, const sgf_core::UniformId & uniformId):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->uniformId = uniformId;
    }

    Uniform::~Uniform() {
    }

    void Uniform::setGlobalProvider(const Provider & provider) {
        SetCoreProviderVisitor setCoreProviderVisitor(
            InternalRender(contexts.get<Render>()).RenderContext(),
            impl->uniformId
        );
        std::visit(setCoreProviderVisitor, provider());
    }

    sgf_core::UniformId Uniform::getUniformId() const {
        return impl->uniformId;
    }
}
