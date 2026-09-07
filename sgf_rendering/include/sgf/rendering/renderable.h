#pragma once

#include <string>
#include <sgf/utils/resource.h>
#include "./material_id.h"
#include "./mesh_id.h"
#include "./renderable_id.h"
#include "./transform.h"
#include "./uniform_provider.h"

namespace sgf_core {
    class RenderContext;

    class Renderable: public Resource<Renderable, RenderableId> {
    public:
        static const std::string TypeName;
        struct Construct {
            MeshId meshId;
            MaterialId materialId;
        };
        Renderable(const Id & id, const Construct & constructParameter);

        void setMeshId(const MeshId & meshId);
        void setMaterialId(const MaterialId & materialId);
        void setTransform(const Transform & transform);

        UniformProvider & getUniformProvider();
        const UniformProvider & getUniformProvider() const;

        glm::vec4 getColor() const;
        
        Transform & getTransform();
        const Transform & getTransform() const;

        void update();
        void render(const RenderContext & context) const;
        void setColor(float r, float g, float b, float a);

    protected:
        MeshId meshId;
        MaterialId materialId;

        glm::vec4 color;

        Transform transform;

        UniformProvider uniformProvider;
    };
}
