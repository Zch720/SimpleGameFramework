#include <gtest/gtest.h>

#include <sgf/platform/platform_context.h>
#include <sgf/rendering/render_context.h>
#include <sgf/rendering/renderable.h>
#include <sgf/rendering/image_loader.h>
#include <sgf/utils/file/fileio.h>
#include "../include/sgf/rendering/font/font_render_context.h"
#include "../include/sgf/rendering/font/text.h"

#include <time.h>

TEST(TestSuite, Test) {
    sgf_core::PlatformContext platformContext;
    platformContext.createWindow({
        .width = 600, .height = 600,
        .title = "Test Window"
    });

    sgf_core::RenderContext renderContext;
    renderContext.initialize();
    platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());

    renderContext.Camera().translateZ(5);
    renderContext.Camera().projection().setProjectionData({
        .type = sgf_core::Projection::Type::ORTHOGRAPHIC,
        .width = 600, .height = 600,
        .near = 0.1, .far = 1000
    });
    renderContext.Camera().update();

    sgf_font::FontRenderContext fontRenderContext(renderContext);
    fontRenderContext.setDpi(platformContext.getPrimaryMonitorDpi());

    std::u32string message = U"abcdefghijkl";

    sgf_font::FontId fontId = fontRenderContext.addFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");

    sgf_font::Text text(fontRenderContext, fontId, 32, U"");
    text.getTransform().setPosition({ -270, 0, 0 });
    text.update(fontRenderContext);

    time_t lastT, t;
    time(&lastT);

    while (!platformContext.Window().isClose()) {
        platformContext.Runtime().onFrameBegin();

        if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            platformContext.Window().close();
        }

        time(&t);
        text.setText(message.substr(0, t - lastT + 1));
        if (t - lastT >= 10) {
            lastT = t;
        }

        text.update(fontRenderContext);
        fontRenderContext.updateFontsAtlasTexture();

        fontRenderContext.TextRenderer().render(text, fontRenderContext.getDefaultMaterialId());

        platformContext.Runtime().onFrameEnd();
    }

    renderContext.destroyAllResources();
    platformContext.terminate();
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
