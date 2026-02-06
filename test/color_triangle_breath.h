#include "sgf/rendering/material.h"
#include "sgf/rendering/projection.h"
#include "sgf/rendering/uniform.h"
#include <gtest/gtest.h>
#include <sgf/control/game_control_context.h>
#include <sgf/rendering/font/font_render_context.h>
#include <sgf/rendering/font/text.h>

class ColorTriangleBreathSuite: public testing::Test {
protected:
    void SetUp() override {
        layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
        layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
    }

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

    float vertices[18] {
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top (Red)
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom Left (Green)
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom Right (Blue)
    };
    uint32_t indices[3] {0, 1, 2};
    sgf_core::VertexLayout layout;
};

TEST_F(ColorTriangleBreathSuite, Breath) {
    sgf_core::PlatformContext platformContext;
    platformContext.createWindow({ .width = 800, .height = 800, .title = "Test Window" });

    sgf_core::RenderContext renderContext;
    renderContext.initialize();
    platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());

    renderContext.Camera().translateZ(5);
    renderContext.Camera().projection().setProjectionData({
        .type = sgf_core::Projection::ORTHOGRAPHIC,
        .width = 3, .height = 3,
        .near = 0.1, .far = 1000
    });

    sgf_font::FontRenderContext fontRenderContext(renderContext);
    sgf_core::MaterialId fontMaterialId = renderContext.MaterialManager.create({
        .useTexture = true,
        .shaderId = fontRenderContext.getShaderId(),
        .textureId = sgf_core::Texture2DId()
    });
    fontRenderContext.setMaterial(fontMaterialId);
    sgf_core::UniformId projectionUniformId = renderContext.MaterialManager.getRef(fontMaterialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CUSTOM);
    renderContext.MaterialManager.getRef(fontMaterialId).registerUniform(renderContext, "transform", sgf_core::UniformSource::TRANSFORM_MATRIX);
    renderContext.MaterialManager.getRef(fontMaterialId).registerUniform(renderContext, "textColor", sgf_core::UniformSource::RENDERABLE_COLOR);

    sgf_core::Projection fontProjection;
    fontProjection.setProjectionData({
        .type = sgf_core::Projection::ORTHOGRAPHIC,
        .width = 800, .height = 800,
        .near = 0, .far = 1000
    });
    renderContext.UniformProvider().setProviderFunc(projectionUniformId, [&fontProjection]() {
        return fontProjection.getProjectionMatrix();
    });

    sgf_font::FontId fontId = fontRenderContext.addFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");
    sgf_font::Text text1(fontRenderContext, fontId, 28, U"This is a colorful triangle");
    text1.position({ -text1.getWidth() / 2, 320, 0 });
    sgf_font::Text text2(fontRenderContext, fontId, 20, U"Press ESC to leave");
    text2.position({ -text2.getWidth() / 2, 310 - text2.getHeight(), 0 });
    
    sgf_core::GameControlContext gameContext(renderContext, platformContext);

    
    sgf_core::ShaderId shaderId = renderContext.ShaderManager.create({
        .vertexShaderSource = vertexShader,
        .fragmentShaderSource = fragmentShader,
    });
    sgf_core::MeshId meshId = renderContext.MeshManager.create({
        .vertices = vertices,
        .verticesCount = 3,
        .indices = indices,
        .indicesCount = 3,
        .vertexLayout = layout,
    });
    sgf_core::MaterialId materialId = renderContext.MaterialManager.create({
        .useTexture = false,
        .shaderId = shaderId,
    });
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CAMERA_PROJECTION);
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "view", sgf_core::UniformSource::CAMERA_VIEW);
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

    sgf_core::RenderableId renderableId = renderContext.RenderableManager.create({
        .meshId = meshId,
        .materialId = materialId,
    });

    gameContext.GameLoop().addRenderFunction([&renderContext, &renderableId](const sgf_core::RenderContext & context) {
        renderContext.RenderableManager.getRef(renderableId).render(context);
    });
    gameContext.GameLoop().addRenderFunction([&fontRenderContext, &text1, &text2](const auto &) {
        text1.render(fontRenderContext);
        text2.render(fontRenderContext);
    });

    gameContext.GameLoop().addUpdateFunction([&renderContext]() {
        renderContext.Camera().update();
    });
    gameContext.GameLoop().addUpdateFunction([&renderContext, &renderableId, &gameContext]() {
        renderContext.RenderableManager.getRef(renderableId).rotateX(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderContext.RenderableManager.getRef(renderableId).rotateY(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderContext.RenderableManager.getRef(renderableId).rotateZ(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderContext.RenderableManager.getRef(renderableId).update();
    });
    gameContext.GameLoop().addUpdateFunction([&fontRenderContext, &text1, &text2]() {
        fontRenderContext.updateFontsAtlasTexture();
        text1.update(fontRenderContext);
        text2.update(fontRenderContext);
    });
    gameContext.GameLoop().addUpdateFunction([&platformContext, &gameContext]() {
        if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            gameContext.GameLoop().stop();
        }
    });

    gameContext.GameLoop().run();

    renderContext.destroyAllResources();
    platformContext.terminate();
}

class ColorCubeBreathSuite: public testing::Test {
protected:
    void SetUp() override {
        layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
        layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
    }

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

    float vertices[144] {
         0.5,  0.5,  0.5,   1.0, 0.0, 0.0,
         0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
        -0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
        -0.5,  0.5,  0.5,   1.0, 0.0, 0.0,

         0.5,  0.5, -0.5,   0.0, 1.0, 0.0,
         0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
        -0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
        -0.5,  0.5, -0.5,   0.0, 1.0, 0.0,

         0.5, -0.5, -0.5,   1.0, 0.0, 0.0,
         0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
        -0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
        -0.5, -0.5, -0.5,   1.0, 0.0, 0.0,

         0.5, -0.5,  0.5,   0.0, 1.0, 0.0,
         0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
        -0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
        -0.5, -0.5,  0.5,   0.0, 1.0, 0.0,

         0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
         0.5, -0.5, -0.5,   0.0, 0.0, 1.0,
         0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
         0.5,  0.5,  0.5,   0.0, 0.0, 1.0,

        -0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
        -0.5, -0.5, -0.5,   0.0, 0.0, 1.0,
        -0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
        -0.5,  0.5,  0.5,   0.0, 0.0, 1.0,
    };
    uint32_t indices[36] {
         0,  1,  2,    0,  2,  3,
         4,  5,  6,    4,  6,  7,
         8,  9, 10,    8, 10, 11,
        12, 13, 14,   12, 14, 15,
        16, 17, 18,   16, 18, 19,
        20, 21, 22,   20, 22, 23,
    };
    sgf_core::VertexLayout layout;
};

TEST_F(ColorCubeBreathSuite, Breath) {
    sgf_core::PlatformContext platformContext;
    platformContext.createWindow({ .width = 800, .height = 800, .title = "Test Window" });

    sgf_core::RenderContext renderContext;
    renderContext.initialize();
    platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());

    renderContext.Camera().translateZ(5);
    renderContext.Camera().projection().setProjectionData({
        .type = sgf_core::Projection::PERSPECTIVE,
        .width = 2, .height = 2,
        .near = 0.1, .far = 1000,
        .fieldOfView = 45
    });

    sgf_font::FontRenderContext fontRenderContext(renderContext);
    sgf_core::MaterialId fontMaterialId = renderContext.MaterialManager.create({
        .useTexture = true,
        .shaderId = fontRenderContext.getShaderId(),
        .textureId = sgf_core::Texture2DId()
    });
    fontRenderContext.setMaterial(fontMaterialId);
    sgf_core::UniformId projectionUniformId = renderContext.MaterialManager.getRef(fontMaterialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CUSTOM);
    renderContext.MaterialManager.getRef(fontMaterialId).registerUniform(renderContext, "transform", sgf_core::UniformSource::TRANSFORM_MATRIX);
    renderContext.MaterialManager.getRef(fontMaterialId).registerUniform(renderContext, "textColor", sgf_core::UniformSource::RENDERABLE_COLOR);

    sgf_core::Projection fontProjection;
    fontProjection.setProjectionData({
        .type = sgf_core::Projection::ORTHOGRAPHIC,
        .width = 800, .height = 800,
        .near = 0, .far = 1000
    });
    renderContext.UniformProvider().setProviderFunc(projectionUniformId, [&fontProjection]() {
        return fontProjection.getProjectionMatrix();
    });

    sgf_font::FontId fontId = fontRenderContext.addFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");
    sgf_font::Text text1(fontRenderContext, fontId, 28, U"This is a three color cube");
    text1.position({ -text1.getWidth() / 2, 320, 0 });
    sgf_font::Text text2(fontRenderContext, fontId, 20, U"Press ESC to leave");
    text2.position({ -text2.getWidth() / 2, 310 - text2.getHeight(), 0 });
    
    sgf_core::GameControlContext gameContext(renderContext, platformContext);

    
    sgf_core::ShaderId shaderId = renderContext.ShaderManager.create({
        .vertexShaderSource = vertexShader,
        .fragmentShaderSource = fragmentShader,
    });
    sgf_core::MeshId meshId = renderContext.MeshManager.create({
        .vertices = vertices,
        .verticesCount = 24,
        .indices = indices,
        .indicesCount = 36,
        .vertexLayout = layout,
    });
    sgf_core::MaterialId materialId = renderContext.MaterialManager.create({
        .useTexture = false,
        .shaderId = shaderId,
    });
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CAMERA_PROJECTION);
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "view", sgf_core::UniformSource::CAMERA_VIEW);
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

    sgf_core::RenderableId renderableId = renderContext.RenderableManager.create({
        .meshId = meshId,
        .materialId = materialId,
    });

    gameContext.GameLoop().addRenderFunction([&renderContext, &renderableId](const sgf_core::RenderContext & context) {
        renderContext.RenderableManager.getRef(renderableId).render(context);
    });
    gameContext.GameLoop().addRenderFunction([&fontRenderContext, &text1, &text2](const auto &) {
        text1.render(fontRenderContext);
        text2.render(fontRenderContext);
    });

    gameContext.GameLoop().addUpdateFunction([&renderContext]() {
        renderContext.Camera().update();
    });
    gameContext.GameLoop().addUpdateFunction([&renderContext, &renderableId, &gameContext]() {
        renderContext.RenderableManager.getRef(renderableId).rotateX(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderContext.RenderableManager.getRef(renderableId).rotateY(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderContext.RenderableManager.getRef(renderableId).rotateZ(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderContext.RenderableManager.getRef(renderableId).update();
    });
    gameContext.GameLoop().addUpdateFunction([&fontRenderContext, &text1, &text2]() {
        fontRenderContext.updateFontsAtlasTexture();
        text1.update(fontRenderContext);
        text2.update(fontRenderContext);
    });
    gameContext.GameLoop().addUpdateFunction([&platformContext, &gameContext]() {
        if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            gameContext.GameLoop().stop();
        }
    });

    gameContext.GameLoop().run();

    renderContext.destroyAllResources();
    platformContext.terminate();
}
