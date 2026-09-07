#pragma once

#include <sgf/utils/fwd.h>

namespace sgf_core {
    class RenderContext;

    class Transform;
    class Projection;
    class Camera;
    class ImageLoader;

    class UniformId;
    class UniformProvider;
    class VertexLayout;

    struct ShaderTag;
    using ShaderId = ResourceId<ShaderTag>;
    class Shader;
    class ShaderManager;

    struct MeshTag;
    using MeshId = ResourceId<MeshTag>;
    class Mesh;
    class MeshManager;
    
    struct MaterialTag;
    using MaterialId = ResourceId<MaterialTag>;
    class Material;
    class MaterialManager;

    struct Texture2DData;
    struct Texture2DTag;
    using Texture2DId = ResourceId<Texture2DTag>;
    class Texture2D;
    class Texture2DManager;

    struct RenderableTag;
    using RenderableId = ResourceId<RenderableTag>;
    class Renderable;
    class RenderableManager;
}
