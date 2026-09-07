#pragma once

#include <memory>
#include <string>
#include "sgf/contexts.h"
#include "sgf/core_fwd.h"
#include "sgf/transform.h"

namespace sgf {
    class TextRender;

    class Text {
    public:
        using Contexts = sgf::Contexts<TextRender>;
    
    private:
        friend TextRender;

        struct Impl;

        std::shared_ptr<Impl> impl;

        Contexts contexts;

        sgf::Transform transform;

        Text(const Contexts & contexts, const sgf_font::Text & text, const sgf_core::MaterialId & materialId);

    public:
        ~Text();

        sgf::Transform & Transform();
        const sgf::Transform & Transform() const;

        int getWidth() const;
        int getHeight() const;

        int getSize() const;
        const std::u32string & getText() const;

        void setSize(int size);
        void setText(const std::u32string & text);
        
        void update();
        void render();
    };
}
