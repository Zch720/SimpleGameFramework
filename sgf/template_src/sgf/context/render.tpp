#include "../../../include/sgf/context/render.h"

namespace sgf {
    template <typename Vertex>
    Mesh Render::createMesh(const std::vector<Vertex> vertices, const std::vector<uint32_t> indices) {
        VertexLayout layout = makeVertexLayout<Vertex>();

        std::vector<uint8_t> verticesBytes(
            (uint8_t *)(vertices.data()), 
            (uint8_t *)(vertices.data()) + sizeof(Vertex) * vertices.size()
        );

        return Mesh(
            { *this },
            verticesBytes,
            indices,
            layout.getCore()
        );
    }
}
