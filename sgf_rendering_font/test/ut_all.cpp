#include <gtest/gtest.h>

#include <sgf/control/game_control_context.h>
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

    sgf_core::GameControlContext controlContext(renderContext, platformContext);

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
    float textSize = 20;

    sgf_font::FontId fontId = fontRenderContext.addFont(TEST_RESOURCES_DIR"/jf-openhuninn-2.1.ttf");

    sgf_font::Text text(fontRenderContext, fontId, 32, U"");
    text.position({ -270, 0, 0 });
    text.update(fontRenderContext);

    time_t lastT, t, beginT;
    time(&lastT);
    beginT = lastT;

    controlContext.GameLoop().addUpdateFunction([&platformContext, &controlContext]() {
        if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            controlContext.GameLoop().stop();
        }
    });

    controlContext.GameLoop().addUpdateFunction([&t, &lastT, &beginT, &text, &textSize, &message, &fontRenderContext, &controlContext]() {
        time(&t);
        text.setText(message.substr(0, t - lastT + 1));
        if ((t - beginT) % 9 > 4) {
            textSize -= 4 * controlContext.GameLoop().Time().getDeltaTime();
            text.setSize(textSize);
        } else {
            textSize += 4 * controlContext.GameLoop().Time().getDeltaTime();
            text.setSize(textSize);
        }

        text.update(fontRenderContext);
        fontRenderContext.updateFontsAtlasTexture();
    });

    controlContext.GameLoop().addRenderFunction([&text, &fontRenderContext](const auto &) {
        text.render(fontRenderContext);
    });

    controlContext.GameLoop().run();

    renderContext.destroyAllResources();
    platformContext.terminate();
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
