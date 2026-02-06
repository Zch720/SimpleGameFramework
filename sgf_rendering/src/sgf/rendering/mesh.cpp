#include "../../../include/sgf/rendering/mesh.h"
#include <sgf/utils/exceptions/invalid_state.h>
#include <glad/gl.h>

namespace sgf_core {
    const std::string MeshTag::TypeName = "Mesh";
    const std::string Mesh::TypeName = "Mesh";

    Mesh::Mesh(const Id & id, const Construct & constructParameter):
        type(constructParameter.type),
        verticesCount(constructParameter.verticesCount),
        indicesCount(constructParameter.indicesCount),
        vertexLayout(constructParameter.vertexLayout)
    {
        this->id = id;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        if (type == ResourceType::STATIC) {
            glBufferData(GL_ARRAY_BUFFER, vertexLayout.getStride() * verticesCount, constructParameter.vertices, GL_STATIC_DRAW);
        } else if (type == ResourceType::DYNAMIC) {
            glBufferData(GL_ARRAY_BUFFER, vertexLayout.getStride() * verticesCount, constructParameter.vertices, GL_DYNAMIC_DRAW);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        if (type == ResourceType::STATIC) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indicesCount, constructParameter.indices, GL_STATIC_DRAW);
        } else if (type == ResourceType::DYNAMIC) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indicesCount, constructParameter.indices, GL_DYNAMIC_DRAW);
        }

        vertexLayout.apply();

        unbind();
    }

    Mesh::~Mesh() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    size_t Mesh::getVerticesCount() const {
        return verticesCount;
    }

    size_t Mesh::getIndicesCount() const {
        return indicesCount;
    }

    void Mesh::bind() const {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    void Mesh::unbind() const {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Mesh::updateVertices(void * vertices, size_t count) {
        if (type == ResourceType::STATIC) {
            throw InvalidState("Try to update " + getTypeName() + " vertices with id " + id.toString() + ", but it type is set to static");
        }
        
        bind();

        if (count <= verticesCount) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexLayout.getStride() * count, vertices);
        } else {
            glBufferData(GL_ARRAY_BUFFER, vertexLayout.getStride() * count, nullptr, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexLayout.getStride() * count, vertices);
        }
        verticesCount = count;

        unbind();
    }

    void Mesh::updateIndices(uint32_t * indices, size_t count) {
        if (type == ResourceType::STATIC) {
            throw InvalidState("Try to update " + getTypeName() + " indices with id " + id.toString() + ", but it type is set to static");
        }

        bind();

        if (count <= indicesCount) {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * count, indices);
        } else {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, nullptr, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * count, indices);
        }
        indicesCount = count;

        unbind();
    }
}
