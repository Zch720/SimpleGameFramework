#include "../../../../include/sgf/rendering/font/font_render_context.h"
#include <sgf/rendering/render_context.h>
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/file/fileio.h>
#include <sgf/utils/logger/log.h>

namespace sgf_font {
    FontRenderContext::FontRenderContext(sgf_core::RenderContext & context):
        context(context),
        fontLoader(*this),
        dpi(96)
    {
        context.unsafeExecute([](const auto &) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }); // TODO: move to sgf_rendering for pre object

        shaderId = context.ShaderManager.create({
            .vertexShaderSource = sgf_core::FileIO::read(RESOURCES_DIR"/text_vertex_shader.glsl"),
            .fragmentShaderSource = sgf_core::FileIO::read(RESOURCES_DIR"/text_fragment_shader.glsl")
        });
        materialId = context.MaterialManager.create({
            .useTexture = true,
            .shaderId = shaderId,
            .textureId = sgf_core::Texture2DId()
        });
        context.MaterialManager.getRef(materialId)
            .registerUniform(context, "projection", sgf_core::UniformSource::CAMERA_PROJECTION);
        context.MaterialManager.getRef(materialId)
            .registerUniform(context, "view", sgf_core::UniformSource::CAMERA_VIEW);
        context.MaterialManager.getRef(materialId)
            .registerUniform(context, "transform", sgf_core::UniformSource::TRANSFORM_MATRIX);
        context.MaterialManager.getRef(materialId)
            .registerUniform(context, "textColor", sgf_core::UniformSource::RENDERABLE_COLOR);
    }

    FontRenderContext::~FontRenderContext() {
    }

    sgf_core::RenderContext & FontRenderContext::getContext() {
        return context;
    }

    const sgf_core::RenderContext & FontRenderContext::getContext() const {
        return context;
    }

    Font & FontRenderContext::getFont(const FontId & fontId) {
        if (fonts.find(fontId) == fonts.end()) {
            SGF_LOG_ERROR("Try to get font with {}, but not found", fontId.toString());
            throw sgf_core::ResourceNotFound("Try to get font with " + fontId.toString() + ", but not found");
        }
        return fonts.at(fontId);
    }

    const Font & FontRenderContext::getFont(const FontId & fontId) const {
        if (fonts.find(fontId) == fonts.end()) {
            SGF_LOG_ERROR("Try to get font with {}, but not found", fontId.toString());
            throw sgf_core::ResourceNotFound("Try to get font with " + fontId.toString() + ", but not found");
        }
        return fonts.at(fontId);
    }

    sgf_core::ShaderId FontRenderContext::getShaderId() const {
        return shaderId;
    }

    sgf_core::MaterialId FontRenderContext::getMaterialId() const {
        return materialId;
    }

    void FontRenderContext::setMaterial(const sgf_core::MaterialId & materialId) {
        this->materialId = materialId;
    }

    uint32_t FontRenderContext::getDpi() const {
        return dpi;
    }

    void FontRenderContext::setDpi(uint32_t dpi) {
        this->dpi = dpi;
    }

    FontId FontRenderContext::addFont(const std::string & filePath) {
        FontId id = fontIdGenerator.getNewId();
        fontLoader.addFont(id, filePath);
        fonts.insert(std::make_pair(id, Font(id, fontLoader)));
        return id;
    }

    void FontRenderContext::updateFontsAtlasTexture() {
        for (auto & [fontId, font] : fonts) {
            font.updateAtlasTexture(*this);
        }
    }
}
