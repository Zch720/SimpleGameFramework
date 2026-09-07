#pragma once

#include <memory>
#include <vector>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"

namespace sgf {
    class TextRender;
    class Render;

    class Font {
    public:
        using Contexts = sgf::Contexts<TextRender>;

    private:
        friend TextRender;

        struct Impl;
        std::shared_ptr<Impl> impl;

        Contexts contexts;

        Font(const Contexts & contexts, const std::string & fontPath);

        sgf_font::FontId getFontId() const;

    public:
        ~Font();

        void loadCharacters(int size, const std::vector<char32_t> & characters);
        void update();
    };
}
