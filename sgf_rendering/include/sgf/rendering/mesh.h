#pragma once

#include <cstdint>
#include <stdint.h>
#include <sgf/utils/resource.h>
#include "./mesh_id.h"
#include "./resource_type.h"
#include "./vertex_layout.h"

namespace sgf_core {
    class UnsafeGLContext;

    class Mesh: public Resource<Mesh, MeshId> {
    public:
        static const std::string TypeName;
        struct Construct {
            ResourceType type = ResourceType::STATIC;
            void * vertices;
            size_t verticesCount;
            uint32_t * indices;
            size_t indicesCount;
            const VertexLayout & vertexLayout;
        };

        Mesh(const Id & id, const Construct & constructParameter);
        ~Mesh();

        size_t getVerticesCount() const;
        size_t getIndicesCount() const;

        void bind() const;
        void unbind() const;

        void updateVertices(void * vertices, size_t count);
        void updateIndices(uint32_t * indices, size_t count);

    private:
        friend UnsafeGLContext;

        ResourceType type;

        uint32_t VAO;
        uint32_t VBO;
        uint32_t EBO;

        size_t verticesCount;
        size_t indicesCount;

        VertexLayout vertexLayout;
    };
}
