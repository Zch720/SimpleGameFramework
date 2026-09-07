#pragma once

#include <cstdint>
#include <memory>
#include "sgf/core_fwd.h"

namespace sgf {
    class Render;

    class VertexLayout {
    public:
        enum VertexType {
            BYTE,
            UNSIGNED_BYTE,
            SHORT,
            UNSIGNED_SHORT,
            INT,
            UNSIGNED_INT,
            HALF_FLOAT,
            FLOAT,
            DOUBLE,
            INT_2_10_10_10_REV,
            UNSIGNED_INT_2_10_10_10_REV,
            UNSIGNED_INT_10F_11F_11F_REV,
        };

    private:
        friend Render;

        struct Impl;

        std::shared_ptr<Impl> impl;

        const sgf_core::VertexLayout & getCore() const;

    public:
        VertexLayout();
        ~VertexLayout();

        void addAttribute(uint32_t index, uint32_t size, VertexType type, bool normalized, size_t offset);
    };

    
    template <typename Vertex>
    VertexLayout makeVertexLayout();

#define SGF_VERTEX(VertexT, ...)                    \
namespace sgf {                                     \
    template<>                                      \
    VertexLayout makeVertexLayout<VertexT>() {      \
        using _VERTEX = VertexT;                    \
        VertexLayout layout;                        \
        __VA_ARGS__                                 \
        return layout;                              \
    }                                               \
}

#define SGF_VERTEX_ATTR(index, member, valueType)   \
layout.addAttribute(                                \
    index,                                          \
    sizeof(_VERTEX::member),                        \
    VertexLayout::VertexType::valueType,            \
    false,                                          \
    offsetof(_VERTEX, member)                       \
);

}
