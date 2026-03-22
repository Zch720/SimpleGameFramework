# Simple Game Framework

This is a game library based on GLFW. It is designed to be simple and easy to manage windows and rendering object.

<!-- ## Features

- [x] Manage windows
- [x] Manage shaders
- [ ] Provide basic rendering objects: include line, triangle, rectangle, circle, image, text, etc.
- [x] Manage audios
- [x] Manage user input -->

## Libraries

This framework is not finished yet. But there are some libraries available:

- `sgf_rendering`: Provides OpenGL-based rendering. Includes components such as `Shader`, `Material`, `Texture2D`, and `Mesh`.
    - `sgf_rendering_font`: A plugin for `sgf_rendering` that loads `.ttf` files and renders text.
- `sgf_platform`: Manages windows and user input.
- `sgf_audio`: Manages audio playing.

## Usage

### Require

- C++ 17
- CMake 3.14 or later

<!-- #### Require Libraries

Ubuntu: `sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev` -->

#### OS

- Windows: support
- Linux: support
- MacOS: not tested

### CMake

To use the sub-libraries in this project, link against the following CMake targets:

- `sgf_rendering`: `sgf_rendering`
    - For developing a plugin that requires direct OpenGL access, also link `sgf_rendering_unsafe`.
- `sgf_rendering_font`: `sgf_rendering_font`
- `sgf_platform`: `sgf_platform`
- `sgf_audio`: `sgf_audio`

## Example

### Create a window with RGB triangle

> This example is based on `GameControlContext` from `sgf_core` and does not reflect the final design of SGF.

```cpp
#include <sgf/control/game_control_context.h>

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


int main() {
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

    sgf_core::GameControlContext gameContext(renderContext, platformContext);

    sgf_core::ShaderId shaderId = renderContext.ShaderManager().create({
        .vertexShaderSource = vertexShader,
        .fragmentShaderSource = fragmentShader,
    });
    sgf_core::VertexLayout layout;
    layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
    layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
    sgf_core::MeshId meshId = renderContext.MeshManager().create({
        .vertices = vertices,
        .verticesCount = 3,
        .indices = indices,
        .indicesCount = 3,
        .vertexLayout = layout,
    });
    sgf_core::MaterialId materialId = renderContext.MaterialManager().create({
        .useTexture = false,
        .shaderId = shaderId,
    });
    renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "projection", sgf_core::UniformSource::CAMERA_PROJECTION);
    renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "view", sgf_core::UniformSource::CAMERA_VIEW);
    renderContext.MaterialManager().getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

    sgf_core::RenderableId renderableId = renderContext.RenderableManager().create({
        .meshId = meshId,
        .materialId = materialId,
    });

    gameContext.GameLoop().addRenderFunction([&renderContext, &renderableId](const sgf_core::RenderContext & context) {
        renderContext.RenderableManager().getRef(renderableId).render(context);
    });

    gameContext.GameLoop().addUpdateFunction([&renderContext]() {
        renderContext.Camera().update();
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
```
