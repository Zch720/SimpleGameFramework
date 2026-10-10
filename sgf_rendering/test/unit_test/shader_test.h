#include <gtest/gtest.h>

#include "sgf/rendering/manager/shader_manager.h"

class ShaderSuite: public testing::Test {
protected:
    std::string sVertexShaderSource = "#version 330 core"\
                                      "layout (location = 0) in vec3 aPos;"\
                                      "void main() {"\
                                      "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"\
                                      "}";
    std::string sFragmentShaderSource = "#version 330 core"\
                                        "uniform vec4 color;"\
                                        "out vec4 FragColor;"\
                                        "void main() {"\
                                        "    FragColor = color;"\
                                        "}";
};

TEST_F(ShaderSuite, CreateShader) {
    sgf::rendering::ShaderManager oManager;
    oManager.create({
        .sVertexShaderSource = sVertexShaderSource,
        .sFragmentShaderSource = sFragmentShaderSource
    });
}
