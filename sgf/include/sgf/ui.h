#pragma once

#include <memory>
#include <sgf/type/rect.h>
#include "sgf/contexts.h"
#include "sgf/context/render.h"

namespace sgf_font {
    class FontRenderContext;
}

namespace sgf {
    class GameContext;
    class GameLoopContext;

    class UI {
    public:
        using UIContexts = sgf::Contexts<Render>;

    private:
        friend GameContext;
        friend GameLoopContext;

        struct Impl;

        UIContexts contexts;

        std::unique_ptr<Impl> impl;

        Rect size;

        Material uiTextMaterial;

        UI(const UIContexts & contexts);
        UI(const UIContexts & contexts, const Rect & size);

        void createProjection();
        void createUITextMaterial();

    public:
        ~UI();

        Rect getSize() const;
        void setSize(const Rect & size);

        Text createText(const Font & font, int size, const std::u32string & text);
    };
}
