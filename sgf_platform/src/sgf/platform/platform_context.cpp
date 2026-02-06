#include "../../../include/sgf/platform/platform_context.h"
#include <GLFW/glfw3.h>
#include <sgf/utils/exceptions/invalid_state.h>
#include "../../../include/sgf/platform/gl_control.h"

namespace sgf_core {
    PlatformContext::PlatformContext(): defaultWindowId(), isInitialized(false), runtime(*this) {
    }

    void PlatformContext::createWindow(const Window::Construct & windowConstruct) {
        if (!defaultWindowId.isDefault()) {
            throw InvalidState("Already created a default window. Multiple windows are not supported yet.");
        }

        if (!isInitialized) {
            GLControl::initGLFW();
        }
        defaultWindowId = windowManager.create(windowConstruct);
        windowManager.getRef(defaultWindowId).setKeyboardInputInjector(*runtime.keyboardInjector);
        windowManager.getRef(defaultWindowId).setMouseInputInjector(*runtime.mouseInjector);
        if (!isInitialized) {
            windowManager.getRef(defaultWindowId).makeContextCurrent();
            GLControl::initGlad();
            isInitialized = true;
        }
    }

    void PlatformContext::terminate() {
        if (!isInitialized) {
            throw InvalidState("PlatformContext has not initialize yet, or you already terminated. Please create a window to initial PlatformContext.");
        }
        windowManager.destroyAll();
        GLControl::terminate();
        isInitialized = false;
    }

    sgf_core::PlatformRuntime & PlatformContext::Runtime() {
        return runtime;
    }

    sgf_core::Window & PlatformContext::Window() const {
        if (defaultWindowId.isDefault()) {
            throw InvalidState("The default window has not been created yet. Please use PlatformContext::createWindow to create the default window.");
        }
        return windowManager.getRef(defaultWindowId);
    }

    uint32_t PlatformContext::getWindowClearBuffer() const {
        return windowClearBuffer;
    }

    void PlatformContext::setWindowClearBuffer(uint32_t buffer) {
        windowClearBuffer = buffer;
    }

    uint32_t PlatformContext::getPrimaryMonitorDpi() const {
        GLFWmonitor * monitor = glfwGetPrimaryMonitor();

        if (monitor != nullptr) {
            int width_px, height_px;
            const GLFWvidmode * mode = glfwGetVideoMode(monitor);
            if (mode != nullptr) {
                width_px = mode->width,
                height_px = mode->height;

                int width_mm, height_mm;
                glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);

                if (width_mm > 0 && height_mm > 0) {
                    double width_inches = width_mm / 25.4;
                    return width_px / width_inches;
                }
            }
        }

        return 96;
    }
}
