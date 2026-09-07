#include "../../../include/sgf/rendering/renderable.h"
#include <glad/gl.h>
#include "../../../include/sgf/rendering/render_context.h"
#include "sgf/rendering/transform.h"

namespace sgf_core {
    const std::string RenderableTag::TypeName = "Renderable";
    const std::string Renderable::TypeName = "Renderable";

    Renderable::Renderable(const Id & id, const Construct & constructParameter):
            meshId(constructParameter.meshId),
            materialId(constructParameter.materialId),
            color(1.0f)
    {
        this->id = id;
    }

    void Renderable::setMeshId(const MeshId & meshId) {
        this->meshId = meshId;
    }

    void Renderable::setMaterialId(const MaterialId & materialId) {
        this->materialId = materialId;
    }

    void Renderable::setTransform(const Transform & transform) {
        this->transform = transform;
    }

    UniformProvider & Renderable::getUniformProvider() {
        return uniformProvider;
    }

    const UniformProvider & Renderable::getUniformProvider() const {
        return uniformProvider;
    }

    glm::vec4 Renderable::getColor() const {
        return color;
    }

    Transform & Renderable::getTransform() {
        return transform;
    }

    const Transform & Renderable::getTransform() const {
        return transform;
    }

    void Renderable::update() {
        transform.updateTransformationMatrix();
    }

    void Renderable::render(const RenderContext & context) const {
        if (!context.MaterialManager().isExist(materialId)) return;
        if (!context.MeshManager().isExist(meshId)) return;

        Material & material = context.MaterialManager().getRef(materialId);
        material.bind(context);
        material.applyPerObject(context, *this);

        Mesh & mesh = context.MeshManager().getRef(meshId);
        mesh.bind();
        glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        mesh.unbind();
    }

    void Renderable::setColor(float r, float g, float b, float a) {
        color = glm::vec4(r, g, b, a);
    }
}
