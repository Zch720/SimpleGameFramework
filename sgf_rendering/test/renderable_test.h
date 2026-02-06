#include <gtest/gtest.h>
#include "./test_env.h"
#include "./utils.h"
#include "../include/sgf/rendering/render_context.h"
#include "../include/sgf/rendering/renderable.h"

using namespace glm;
using namespace sgf_core;

class RenderableSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        sgf_test::createOpenGLContext();

        context.initialize();
        shaderId = context.ShaderManager().create({
            .vertexShaderSource = vertexShaderSource,
            .fragmentShaderSource = fragmentShaderSource
        });
        materialId = context.MaterialManager().create({ .useTexture = false, .shaderId = shaderId });
        context.MaterialManager().getRef(materialId).registerUniform(context, "model", UniformSource::TRANSFORM_MATRIX);
        context.MaterialManager().getRef(materialId).registerUniform(context, "color", UniformSource::RENDERABLE_COLOR);
        triangleVertexLayout = VertexLayout();
        triangleVertexLayout.addAttribute({ .index = 0, .size = 3, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });
        triangleMeshId = context.MeshManager().create({ .vertices = triangleVertices.data(), .verticesCount = 3, .indices = triangleIndices.data(), .indicesCount = 3, .vertexLayout = triangleVertexLayout });
    }

    virtual void TearDown() {
        context.destroyAllResources();

        sgf_test::OpenGLContextTerminate();
    }

    RenderContext context;
    ShaderId shaderId;
    MaterialId materialId;
    VertexLayout triangleVertexLayout;
    MeshId triangleMeshId;
    std::vector<float> triangleVertices {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> triangleIndices { 0, 1, 2 };
    
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 model = mat4(1.0);
        void main() {
            gl_Position = model * vec4(aPos, 1.0);
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        uniform vec4 color = vec4(1.0);
        out vec4 FragColor;
        void main() {
            FragColor = color;
        }
    )";

    vec2 point1 { 0.0f, 0.5f };
    vec2 point2 { -0.5f, -0.5f };
    vec2 point3 { 0.5f, -0.5f };
};

TEST_F(RenderableSuite, DrawTriangle) {
    if (skipHandTest) GTEST_SKIP();

    std::vector<float> vertices {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });
    MeshId meshId = context.MeshManager().create({ .vertices = (void *)vertices.data(), .verticesCount = 3, .indices = indices.data(), .indicesCount = 3, .vertexLayout = vertexLayout });

    RenderableId triangleId = context.RenderableManager().create({ .meshId = meshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, DrawRectangle) {
    if (skipHandTest) GTEST_SKIP();

    std::vector<float> vertices {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2, 0, 2, 3 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });
    MeshId meshId = context.MeshManager().create({ .vertices = (void *)vertices.data(), .verticesCount = 4, .indices = indices.data(), .indicesCount = 6, .vertexLayout = vertexLayout });

    RenderableId rectangleId = context.RenderableManager().create({ .meshId = meshId, .materialId = materialId });

    PRINTF("There should be a white Rectangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(rectangleId).update();
        context.RenderableManager().getRef(rectangleId).render(context);
    });
}

TEST_F(RenderableSuite, DrawPentagon) {
    if (skipHandTest) GTEST_SKIP();

    std::vector<float> vertices {
        -0.65f, 0.25f, 0.0f,
        0.0f, 0.7f, 0.0f,
        0.65f, 0.25f, 0.0f,
        0.4f, -0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2, 0, 2, 3, 0, 3, 4 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });
    MeshId meshId = context.MeshManager().create({ .vertices = (void *)vertices.data(), .verticesCount = 5, .indices = indices.data(), .indicesCount = 9, .vertexLayout = vertexLayout });

    RenderableId pentagonId = context.RenderableManager().create({ .meshId = meshId, .materialId = materialId });

    PRINTF("There should be a white Rectangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(pentagonId).update();
        context.RenderableManager().getRef(pentagonId).render(context);
    });
}

TEST_F(RenderableSuite, SetColor) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });
    context.RenderableManager().getRef(triangleId).setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a red triangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, ChangeColorAtRuntime) {
    if (skipHandTest) GTEST_SKIP();

    glm::vec3 colors[] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });
    context.RenderableManager().getRef(triangleId).setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a triangle on the screen\n");
    PRINTF("The triangle should change color between red, green and blue\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 200;
    int colorIndex = 0;
    WINDOW_LOOP("Window display wrong", {
        if (--count == 0) {
            count = 200;
            context.RenderableManager().getRef(triangleId).setColor(colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, 1.0f);
            colorIndex = (colorIndex + 1) % 3;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, Translate) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).translate({delta, delta, 0});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, TranslateX) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between left and right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).translateX(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, TranslateY) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between up and down\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).translateY(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, TranslateZ) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangle1Id = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });
    RenderableId triangle2Id = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });
    context.RenderableManager().getRef(triangle2Id).setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a white triangle and red triangle on the screen by terns\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangle1Id).translateZ(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangle1Id).update();
        context.RenderableManager().getRef(triangle1Id).render(context);
        context.RenderableManager().getRef(triangle2Id).update();
        context.RenderableManager().getRef(triangle2Id).render(context);
    });
}

TEST_F(RenderableSuite, SetPosition) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 pos = context.RenderableManager().getRef(triangleId).position();
        context.RenderableManager().getRef(triangleId).position({pos.x + delta, pos.y + delta, pos.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, Scale) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically and horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 scale = context.RenderableManager().getRef(triangleId).scale();
        context.RenderableManager().getRef(triangleId).scale({scale.x + delta, scale.y + delta, scale.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, ScaleX) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 scale = context.RenderableManager().getRef(triangleId).scale();
        context.RenderableManager().getRef(triangleId).scaleX(scale.x + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, ScaleY) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 scale = context.RenderableManager().getRef(triangleId).scale();
        context.RenderableManager().getRef(triangleId).scaleY(scale.y + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, Rotate) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).rotate({0, 0, delta});

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, RotateX) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around x-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).rotateX(delta);

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, RotateY) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around y-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).rotateY(delta);

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, RotateZ) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around z-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        context.RenderableManager().getRef(triangleId).rotateZ(delta);

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}

TEST_F(RenderableSuite, SetRotation) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = context.RenderableManager().create({ .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 rotation = context.RenderableManager().getRef(triangleId).rotation();
        context.RenderableManager().getRef(triangleId).rotation({rotation.x, rotation.y, rotation.z + delta});

        context.RenderableManager().getRef(triangleId).update();
        context.RenderableManager().getRef(triangleId).render(context);
    });
}
