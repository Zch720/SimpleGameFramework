#pragma once

#include <functional>
#include <memory>
#include <variant>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"
#include "sgf/type/vec2.h"
#include "sgf/type/vec3.h"
#include "sgf/type/vec4.h"
#include "sgf/type/mat2.h"
#include "sgf/type/mat2x3.h"
#include "sgf/type/mat2x4.h"
#include "sgf/type/mat3.h"
#include "sgf/type/mat3x2.h"
#include "sgf/type/mat3x4.h"
#include "sgf/type/mat4.h"
#include "sgf/type/mat4x2.h"
#include "sgf/type/mat4x3.h"

namespace sgf {
    class Render;

    enum class UniformSource: int {
        TRANSFORM,
        RENDERABLE_COLOR,
        CAMERA_VIEW,
        CAMERA_PROJECTION,
        CUSTOM
    };

    using UniformValue = std::variant<
        int,
        float,
        Vec2,
        Vec3,
        Vec4,
        Mat2,
        Mat3,
        Mat4,
        Mat2x3,
        Mat3x2,
        Mat2x4,
        Mat4x2,
        Mat3x4,
        Mat4x3
    >;

    class Uniform {
    public:
        using Contexts = sgf::Contexts<Render>;
        using Provider = std::function<UniformValue()>;

    private:
        friend Render;

        struct Impl;

        std::shared_ptr<Impl> impl;

        Contexts contexts;

        Uniform(const Contexts & contexts, const sgf_core::UniformId & uniformId);

        sgf_core::UniformId getUniformId() const;

    public:
        ~Uniform();

        void setGlobalProvider(const Provider & provider);
    };
}
