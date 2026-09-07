#pragma once

#include <sgf/utils/fwd.h>

namespace sgf_core {
    class PlatformContext;
    class PlatformRuntime;
    
    struct WindowTag;
    using WindowId = ResourceId<WindowTag>;
    class Window;
    class WindowManager;

    enum class Key: int;
    class Input;
    class Keyboard;
    class Mouse;
}
