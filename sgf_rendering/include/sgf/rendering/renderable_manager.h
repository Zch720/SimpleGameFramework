#pragma once

#include <sgf/utils/manager.h>
#include "./renderable.h"

namespace sgf_core {
    class RenderableManager: public Manager<Renderable> {
    };
}
