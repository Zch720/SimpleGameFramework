#include <gtest/gtest.h>
#include "sgf/game.h"

class ColorTriangleBreathProceduralSuite: public testing::Test {
public:
    struct Vertex {
        sgf::Vec3 position;
        sgf::Vec3 color;
    };

protected:
    std::string vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;   // The vertex position data
        layout (location = 1) in vec3 aColor;  // The vertex color data
        
        uniform mat4 projection = mat4(1.0);
        uniform mat4 view = mat4(1.0);
        uniform mat4 model = mat4(1.0);

        out vec3 ourColor; // Output a color to the fragment shader

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0); // Set the position
            ourColor = aColor; // Pass the color to the fragment shader
        }
    )";

    std::string fragmentShader = R"(
        #version 330 core
        out vec4 FragColor; // The final output color for the pixel

        in vec3 ourColor; // Input color from the vertex shader (interpolated)

        void main()
        {
            FragColor = vec4(ourColor, 1.0f); // Set the final color, including alpha (opacity)
        }
    )";

    std::vector<Vertex> vertices {
        {{ 0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }}, // Top (Red)
        {{ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }}, // Bottom Left (Green)
        {{ 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }} // Bottom Right (Blue)
    };
    std::vector<uint32_t> indices { 0, 1, 2 };
};

SGF_VERTEX(ColorTriangleBreathProceduralSuite::Vertex,
    SGF_VERTEX_ATTR(0, position, FLOAT)
    SGF_VERTEX_ATTR(1, color, FLOAT)
)

TEST_F(ColorTriangleBreathProceduralSuite, Breath) {
    sgf::Game game({ .width = 800, .height = 800, .title = "Test Window" });
    sgf::GameContext & gameContext = game.GameContext();

    // gameContext.createScene("default");
    // gameContext.switchScene("default");
    
    // gameContext.getCurrentSceneRef().Camera().translateZ(5);
    // gameContext.getCurrentSceneRef().Camera().orthographicProjection({ 3, 3 }, 0.1, 1000);

    gameContext.Camera().translateZ(5);
    gameContext.Camera().orthographicProjection({ 3, 3 }, 0.1, 1000);

    sgf::Font font = gameContext.Render().Text().createFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");
    sgf::Text text1 = gameContext.UI().createText(font, 28, U"This is a colorful triangle");
    text1.Transform().setPosition({ -text1.getWidth() / 2.0f, 320, 0 });
    sgf::Text text2 = gameContext.UI().createText(font, 20, U"Press ESC to leave");
    text2.Transform().setPosition({ -text2.getWidth() / 2.0f, 310.0f - text2.getHeight(), 0 });

    sgf::Shader shader = gameContext.Render().createShader(vertexShader, fragmentShader);
    sgf::Mesh mesh = gameContext.Render().createMesh<Vertex>(vertices, indices);
    sgf::Material material = gameContext.Render().createMaterial(shader);
    material.registerUniform("projection", sgf::UniformSource::CAMERA_PROJECTION);
    material.registerUniform("view", sgf::UniformSource::CAMERA_VIEW);
    material.registerUniform("model", sgf::UniformSource::TRANSFORM);
    sgf::Renderable renderable = gameContext.Render().createRenderable(mesh, material);

    while (!gameContext.isStop()) {
        gameContext.beginFrame();
        
        if (game.PlatformContext().Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            gameContext.stop();
        }

        gameContext.Camera().update();

        // renderable.Transform().rotateX(30 * gameContext.Time().getDeltaTime());
        // renderable.Transform().rotateY(30 * gameContext.Time().getDeltaTime());
        // renderable.Transform().rotateZ(30 * gameContext.Time().getDeltaTime());
        // renderable.update();
        // renderable.render();

        text1.update();
        text2.update();
        font.update();
        text1.render();
        text2.render();

        gameContext.endFrame();
    }
}

// class ColorTriangleBreathSuite: public testing::Test {
// protected:
//     void SetUp() override {
//         layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
//         layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
//     }

//     std::string vertexShader = R"(
//         #version 330 core
//         layout (location = 0) in vec3 aPos;   // The vertex position data
//         layout (location = 1) in vec3 aColor;  // The vertex color data
        
//         uniform mat4 projection = mat4(1.0);
//         uniform mat4 view = mat4(1.0);
//         uniform mat4 model = mat4(1.0);

//         out vec3 ourColor; // Output a color to the fragment shader

//         void main()
//         {
//             gl_Position = projection * view * model * vec4(aPos, 1.0); // Set the position
//             ourColor = aColor; // Pass the color to the fragment shader
//         }
//     )";

//     std::string fragmentShader = R"(
//         #version 330 core
//         out vec4 FragColor; // The final output color for the pixel

//         in vec3 ourColor; // Input color from the vertex shader (interpolated)

//         void main()
//         {
//             FragColor = vec4(ourColor, 1.0f); // Set the final color, including alpha (opacity)
//         }
//     )";

//     float vertices[18] {
//          0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top (Red)
//         -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom Left (Green)
//          0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom Right (Blue)
//     };
//     uint32_t indices[3] {0, 1, 2};
//     sgf_core::VertexLayout layout;
// };

// TEST_F(ColorTriangleBreathSuite, Breath) {
//     sgf_core::PlatformContext platformContext;
//     platformContext.createWindow({ .width = 800, .height = 800, .title = "Test Window" });

//     sgf_core::RenderContext renderContext;
//     renderContext.initialize();
//     platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());

//     renderContext.Camera().translateZ(5);
//     renderContext.Camera().projection().setProjectionData({
//         .type = sgf_core::Projection::ORTHOGRAPHIC,
//         .width = 3, .height = 3,
//         .near = 0.1, .far = 1000
//     });

//     sgf_font::FontRenderContext fontRenderContext(renderContext);
//     sgf_core::MaterialId fontMaterialId = renderContext.MaterialManager().create({
//         .useTexture = true,
//         .shaderId = fontRenderContext.getShaderId(),
//         .textureId = sgf_core::Texture2DId()
//     });
//     fontRenderContext.setMaterial(fontMaterialId);
//     sgf_core::UniformId projectionUniformId = renderContext.MaterialManager().getRef(fontMaterialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CUSTOM);
//     renderContext.MaterialManager().getRef(fontMaterialId).registerUniform(renderContext, "transform", sgf_core::UniformSource::TRANSFORM_MATRIX);
//     renderContext.MaterialManager().getRef(fontMaterialId).registerUniform(renderContext, "textColor", sgf_core::UniformSource::RENDERABLE_COLOR);

//     sgf_core::Projection fontProjection;
//     fontProjection.setProjectionData({
//         .type = sgf_core::Projection::ORTHOGRAPHIC,
//         .width = 800, .height = 800,
//         .near = 0, .far = 1000
//     });
//     renderContext.UniformProvider().setProviderFunc(projectionUniformId, [&fontProjection]() {
//         return fontProjection.getProjectionMatrix();
//     });

//     sgf_font::FontId fontId = fontRenderContext.addFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");
//     sgf_font::Text text1(fontRenderContext, fontId, 28, U"This is a colorful triangle");
//     text1.position({ -text1.getWidth() / 2, 320, 0 });
//     sgf_font::Text text2(fontRenderContext, fontId, 20, U"Press ESC to leave");
//     text2.position({ -text2.getWidth() / 2, 310 - text2.getHeight(), 0 });
    
//     sgf_core::GameLoopContext gameLoopContext(platformContext, renderContext);

    
//     sgf_core::ShaderId shaderId = renderContext.ShaderManager().create({
//         .vertexShaderSource = vertexShader,
//         .fragmentShaderSource = fragmentShader,
//     });
//     sgf_core::MeshId meshId = renderContext.MeshManager().create({
//         .vertices = vertices,
//         .verticesCount = 3,
//         .indices = indices,
//         .indicesCount = 3,
//         .vertexLayout = layout,
//     });
//     sgf_core::MaterialId materialId = renderContext.MaterialManager().create({
//         .useTexture = false,
//         .shaderId = shaderId,
//     });
//     renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CAMERA_PROJECTION);
//     renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "view", sgf_core::UniformSource::CAMERA_VIEW);
//     renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

//     sgf_core::RenderableId renderableId = renderContext.RenderableManager().create({
//         .meshId = meshId,
//         .materialId = materialId,
//     });

//     sgf_core::RenderLayerId defaultLayer = gameLoopContext.RenderPipeline().addLayer("default", 0);
//     sgf_core::RenderLayerId uiLayer = gameLoopContext.RenderPipeline().addLayer("ui", 100);
//     gameLoopContext.RenderPipeline().addRenderFunc(defaultLayer, [&renderContext, &renderableId]() {
//         renderContext.RenderableManager().getRef(renderableId).render(renderContext);
//     });
//     gameLoopContext.RenderPipeline().addRenderFunc(uiLayer, [&fontRenderContext, &text1, &text2]() {
//         text1.render(fontRenderContext);
//         text2.render(fontRenderContext);
//     });

//     gameLoopContext.UpdatePipeline().addUpdateFunc([&renderContext]() {
//         renderContext.Camera().update();
//     });
//     gameLoopContext.UpdatePipeline().addUpdateFunc([&renderContext, &renderableId, &gameLoopContext]() {
//         renderContext.RenderableManager().getRef(renderableId).rotateX(30 * gameLoopContext.Runtime().Time().getDeltaTime());
//         renderContext.RenderableManager().getRef(renderableId).rotateY(30 * gameLoopContext.Runtime().Time().getDeltaTime());
//         renderContext.RenderableManager().getRef(renderableId).rotateZ(30 * gameLoopContext.Runtime().Time().getDeltaTime());
//         renderContext.RenderableManager().getRef(renderableId).update();
//     });
//     gameLoopContext.UpdatePipeline().addUpdateFunc([&fontRenderContext, &text1, &text2]() {
//         text1.update(fontRenderContext);
//         text2.update(fontRenderContext);
//     });
//     gameLoopContext.UpdatePipeline().addUpdateFunc([&platformContext, &gameLoopContext]() {
//         if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
//             gameLoopContext.stop();
//         }
//     });

//     gameLoopContext.UpdatePipeline().addPostUpdateFunc([&fontRenderContext]() {
//         fontRenderContext.updateFontsAtlasTexture();
//     });

//     gameLoopContext.run();

//     renderContext.destroyAllResources();
//     platformContext.terminate();
// }

// class ColorCubeBreathSuite: public testing::Test {
// protected:
//     void SetUp() override {
//         layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
//         layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
//     }

//     std::string vertexShader = R"(
//         #version 330 core
//         layout (location = 0) in vec3 aPos;   // The vertex position data
//         layout (location = 1) in vec3 aColor;  // The vertex color data
        
//         uniform mat4 projection = mat4(1.0);
//         uniform mat4 view = mat4(1.0);
//         uniform mat4 model = mat4(1.0);

//         out vec3 ourColor; // Output a color to the fragment shader

//         void main()
//         {
//             gl_Position = projection * view * model * vec4(aPos, 1.0); // Set the position
//             ourColor = aColor; // Pass the color to the fragment shader
//         }
//     )";

//     std::string fragmentShader = R"(
//         #version 330 core
//         out vec4 FragColor; // The final output color for the pixel

//         in vec3 ourColor; // Input color from the vertex shader (interpolated)

//         void main()
//         {
//             FragColor = vec4(ourColor, 1.0f); // Set the final color, including alpha (opacity)
//         }
//     )";

//     float vertices[144] {
//          0.5,  0.5,  0.5,   1.0, 0.0, 0.0,
//          0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
//         -0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
//         -0.5,  0.5,  0.5,   1.0, 0.0, 0.0,

//          0.5,  0.5, -0.5,   0.0, 1.0, 0.0,
//          0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
//         -0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
//         -0.5,  0.5, -0.5,   0.0, 1.0, 0.0,

//          0.5, -0.5, -0.5,   1.0, 0.0, 0.0,
//          0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
//         -0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
//         -0.5, -0.5, -0.5,   1.0, 0.0, 0.0,

//          0.5, -0.5,  0.5,   0.0, 1.0, 0.0,
//          0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
//         -0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
//         -0.5, -0.5,  0.5,   0.0, 1.0, 0.0,

//          0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
//          0.5, -0.5, -0.5,   0.0, 0.0, 1.0,
//          0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
//          0.5,  0.5,  0.5,   0.0, 0.0, 1.0,

//         -0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
//         -0.5, -0.5, -0.5,   0.0, 0.0, 1.0,
//         -0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
//         -0.5,  0.5,  0.5,   0.0, 0.0, 1.0,
//     };
//     uint32_t indices[36] {
//          0,  1,  2,    0,  2,  3,
//          4,  5,  6,    4,  6,  7,
//          8,  9, 10,    8, 10, 11,
//         12, 13, 14,   12, 14, 15,
//         16, 17, 18,   16, 18, 19,
//         20, 21, 22,   20, 22, 23,
//     };
//     sgf_core::VertexLayout layout;

//     float rectangleVertices[24] {
//          0.5,  0.5,  0,   1.0, 1.0, 0.0,
//          0.5, -0.5,  0,   1.0, 1.0, 0.0,
//         -0.5, -0.5,  0,   1.0, 1.0, 0.0,
//         -0.5,  0.5,  0,   1.0, 1.0, 0.0,
//     };
//     uint32_t rectangleIndices[6] {
//         0, 1, 2,
//         0, 2, 3
//     };
// };

// TEST_F(ColorCubeBreathSuite, Breath) {
//     sgf_core::PlatformContext platformContext;
//     platformContext.createWindow({ .width = 800, .height = 800, .title = "Test Window" });

//     sgf_core::RenderContext renderContext;
//     renderContext.initialize();
//     platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());

//     renderContext.Camera().translateZ(5);
//     renderContext.Camera().projection().setProjectionData({
//         .type = sgf_core::Projection::PERSPECTIVE,
//         .width = 2, .height = 2,
//         .near = 0.1, .far = 1000,
//         .fieldOfView = 45
//     });

//     sgf_font::FontRenderContext fontRenderContext(renderContext);
//     sgf_core::MaterialId fontMaterialId = renderContext.MaterialManager().create({
//         .useTexture = true,
//         .shaderId = fontRenderContext.getShaderId(),
//         .textureId = sgf_core::Texture2DId()
//     });
//     fontRenderContext.setMaterial(fontMaterialId);
//     sgf_core::UniformId projectionUniformId = renderContext.MaterialManager().getRef(fontMaterialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CUSTOM);
//     renderContext.MaterialManager().getRef(fontMaterialId).registerUniform(renderContext, "transform", sgf_core::UniformSource::TRANSFORM_MATRIX);
//     renderContext.MaterialManager().getRef(fontMaterialId).registerUniform(renderContext, "textColor", sgf_core::UniformSource::RENDERABLE_COLOR);

//     sgf_core::Projection fontProjection;
//     fontProjection.setProjectionData({
//         .type = sgf_core::Projection::ORTHOGRAPHIC,
//         .width = 800, .height = 800,
//         .near = 0, .far = 1000
//     });
//     renderContext.UniformProvider().setProviderFunc(projectionUniformId, [&fontProjection]() {
//         return fontProjection.getProjectionMatrix();
//     });

//     sgf_font::FontId fontId = fontRenderContext.addFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");
//     sgf_font::Text text1(fontRenderContext, fontId, 28, U"This is a three color cube");
//     text1.position({ -text1.getWidth() / 2, 320, 0 });
//     sgf_font::Text text2(fontRenderContext, fontId, 20, U"Press ESC to leave");
//     text2.position({ -text2.getWidth() / 2, 310 - text2.getHeight(), 0 });
    
//     sgf_core::GameLoopContext gameLoopContext(platformContext, renderContext);

    
//     sgf_core::ShaderId shaderId = renderContext.ShaderManager().create({
//         .vertexShaderSource = vertexShader,
//         .fragmentShaderSource = fragmentShader,
//     });
//     sgf_core::MeshId meshId = renderContext.MeshManager().create({
//         .vertices = vertices,
//         .verticesCount = 24,
//         .indices = indices,
//         .indicesCount = 36,
//         .vertexLayout = layout,
//     });
//     sgf_core::MaterialId materialId = renderContext.MaterialManager().create({
//         .useTexture = false,
//         .shaderId = shaderId,
//     });
//     renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CAMERA_PROJECTION);
//     renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "view", sgf_core::UniformSource::CAMERA_VIEW);
//     renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

//     sgf_core::RenderableId renderableId = renderContext.RenderableManager().create({
//         .meshId = meshId,
//         .materialId = materialId,
//     });

//     sgf_core::RenderLayerId defaultLayer = gameLoopContext.RenderPipeline().addLayer("default", 0);
//     sgf_core::RenderLayerId uiLayer = gameLoopContext.RenderPipeline().addLayer("ui", 100);
//     gameLoopContext.RenderPipeline().addRenderFunc(defaultLayer, [&renderContext, &renderableId]() {
//         renderContext.RenderableManager().getRef(renderableId).render(renderContext);
//     });
//     gameLoopContext.RenderPipeline().addRenderFunc(uiLayer, [&fontRenderContext, &text1, &text2]() {
//         text1.render(fontRenderContext);
//         text2.render(fontRenderContext);
//     });

//     gameLoopContext.UpdatePipeline().addUpdateFunc([&renderContext]() {
//         renderContext.Camera().update();
//     });
//     gameLoopContext.UpdatePipeline().addUpdateFunc([&renderContext, &renderableId, &gameLoopContext]() {
//         renderContext.RenderableManager().getRef(renderableId).rotateX(30 * gameLoopContext.Runtime().Time().getDeltaTime());
//         renderContext.RenderableManager().getRef(renderableId).rotateY(30 * gameLoopContext.Runtime().Time().getDeltaTime());
//         renderContext.RenderableManager().getRef(renderableId).rotateZ(30 * gameLoopContext.Runtime().Time().getDeltaTime());
//         renderContext.RenderableManager().getRef(renderableId).update();
//     });
//     gameLoopContext.UpdatePipeline().addUpdateFunc([&fontRenderContext, &text1, &text2]() {
//         text1.update(fontRenderContext);
//         text2.update(fontRenderContext);
//     });
//     gameLoopContext.UpdatePipeline().addUpdateFunc([&platformContext, &gameLoopContext]() {
//         if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
//             gameLoopContext.stop();
//         }
//     });

//     gameLoopContext.UpdatePipeline().addPostUpdateFunc([&fontRenderContext]() {
//         fontRenderContext.updateFontsAtlasTexture();
//     });

//     gameLoopContext.run();

//     renderContext.destroyAllResources();
//     platformContext.terminate();
// }
