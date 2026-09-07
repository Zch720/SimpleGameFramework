#include "sgf/render/material.h"
#include <sgf/rendering/render_context.h>
#include "sgf/context/render.h"
#include "sgf/context/internal_render.h"

namespace sgf {
    struct Material::Impl {
        sgf_core::MaterialId materialId;
    };

    Material::Material(const Contexts & contexts, const sgf_core::MaterialId & materialId):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->materialId = materialId;
    }

    Material::Material(const Contexts & contexts, const sgf_core::ShaderId & shaderId):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->materialId = InternalRender(this->contexts.get<Render>())
            .RenderContext()
            .MaterialManager()
            .create({
                .useTexture = false,
                .shaderId = shaderId
            });
    }

    Material::Material(const Contexts & contexts, const sgf_core::ShaderId & shaderId, const sgf_core::Texture2DId & textureId):
        contexts(contexts),
        impl(std::make_shared<Impl>())
    {
        impl->materialId = InternalRender(this->contexts.get<Render>())
            .RenderContext()
            .MaterialManager()
            .create({
                .useTexture = true,
                .shaderId = shaderId,
                .textureId = textureId
            });
    }

    Material::~Material() {
    }

    bool Material::isUsingTexture() const {
        const InternalRender internalRender(contexts.get<Render>());
        return internalRender
            .RenderContext()
            .MaterialManager()
            .getRef(impl->materialId)
            .getUseTexture();
    }

    void Material::useTexture(bool useTexture) {
        InternalRender(contexts.get<Render>())
            .RenderContext()
            .MaterialManager()
            .getRef(impl->materialId)
            .setUseTexture(useTexture);
    }

    std::optional<Uniform> Material::registerUniform(const std::string & name, UniformSource sourceType) {
        InternalRender internalRender = InternalRender(this->contexts.get<Render>());
        sgf_core::RenderContext & renderContext = internalRender.RenderContext();
        switch (sourceType) {
            case UniformSource::TRANSFORM:
                renderContext.MaterialManager()
                    .getRef(impl->materialId)
                    .registerUniform(renderContext, name, sgf_core::UniformSource::TRANSFORM_MATRIX);
                return std::optional<Uniform>();
            case UniformSource::RENDERABLE_COLOR:
                renderContext.MaterialManager()
                    .getRef(impl->materialId)
                    .registerUniform(renderContext, name, sgf_core::UniformSource::RENDERABLE_COLOR);
                return std::optional<Uniform>();
            case UniformSource::CAMERA_PROJECTION:
                renderContext.MaterialManager()
                    .getRef(impl->materialId)
                    .registerUniform(renderContext, name, sgf_core::UniformSource::CAMERA_PROJECTION);
                return std::optional<Uniform>();
            case UniformSource::CAMERA_VIEW:
                renderContext.MaterialManager()
                    .getRef(impl->materialId)
                    .registerUniform(renderContext, name, sgf_core::UniformSource::CAMERA_VIEW);
                return std::optional<Uniform>();
            case UniformSource::CUSTOM:
                sgf_core::UniformId uniformId = renderContext.MaterialManager()
                    .getRef(impl->materialId)
                    .registerUniform(renderContext, name, sgf_core::UniformSource::CUSTOM);
                return std::optional<Uniform>(internalRender.createUniform(uniformId));
        }
        return std::optional<Uniform>();
    }

    sgf_core::MaterialId Material::getMaterialId() const {
        return impl->materialId;
    }
}
