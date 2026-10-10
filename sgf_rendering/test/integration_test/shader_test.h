#include <gtest/gtest.h>

#include "sgf/rendering/rendering_data_context.h"
#include "sgf/rendering/operator/adapter/shader_operation_adapter.h"
#include "sgf/rendering/operator/opengl/rendering_operate_provider.h"

#include "./utils/opengl_context_utils.hpp"

class ShaderSuite: public testing::Test {
protected:
    std::string m_sVertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";
    std::string m_sFragmentShaderSource = R"(
        #version 330 core
        uniform vec4 color;
        out vec4 FragColor;
        void main() {
            FragColor = color;
        }
    )";

    OpenGLContextGLFW oOpenglContext;

    void SetUp() override {
        oOpenglContext.open();
    }

    void TearDown() override {
        oOpenglContext.terminate();
    }
};

TEST_F(ShaderSuite, BuildShader) {
    sgf::rendering::RenderingDataContext oDataContext;
    sgf::rendering::RenderingOperateProviderOpenGL oOperateContext;
    sgf::rendering::ShaderOperationAdapter oAdapter(oDataContext, oOperateContext);

    sgf::rendering::ShaderId oId = oDataContext.getShaders().create({
        .sVertexShaderSource = m_sVertexShaderSource,
        .sFragmentShaderSource = m_sFragmentShaderSource
    });
    oAdapter.create(oId);
}

TEST_F(ShaderSuite, DestroyShader) {
    sgf::rendering::RenderingDataContext oDataContext;
    sgf::rendering::RenderingOperateProviderOpenGL oOperateContext;
    sgf::rendering::ShaderOperationAdapter oAdapter(oDataContext, oOperateContext);

    sgf::rendering::ShaderId oId = oDataContext.getShaders().create({
        .sVertexShaderSource = m_sVertexShaderSource,
        .sFragmentShaderSource = m_sFragmentShaderSource
    });
    oAdapter.create(oId);

    oAdapter.destroy(oId);
}
