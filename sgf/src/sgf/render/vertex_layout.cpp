#include "sgf/render/vertex_layout.h"
#include "sgf/rendering/vertex_layout.h"
#include <stdio.h>

namespace sgf {
    sgf_core::VertexLayout::VertexType toCore(VertexLayout::VertexType type) {
        switch (type) {
            case VertexLayout::VertexType::BYTE: return sgf_core::VertexLayout::VertexType::BYTE;
            case VertexLayout::VertexType::UNSIGNED_BYTE: return sgf_core::VertexLayout::VertexType::UNSIGNED_BYTE;
            case VertexLayout::VertexType::SHORT: return sgf_core::VertexLayout::VertexType::SHORT;
            case VertexLayout::VertexType::UNSIGNED_SHORT: return sgf_core::VertexLayout::VertexType::UNSIGNED_SHORT;
            case VertexLayout::VertexType::INT: return sgf_core::VertexLayout::VertexType::INT;
            case VertexLayout::VertexType::UNSIGNED_INT: return sgf_core::VertexLayout::VertexType::UNSIGNED_INT;
            case VertexLayout::VertexType::HALF_FLOAT: return sgf_core::VertexLayout::VertexType::HALF_FLOAT;
            case VertexLayout::VertexType::FLOAT: return sgf_core::VertexLayout::VertexType::FLOAT;
            case VertexLayout::VertexType::DOUBLE: return sgf_core::VertexLayout::VertexType::DOUBLE;
            case VertexLayout::VertexType::INT_2_10_10_10_REV: return sgf_core::VertexLayout::VertexType::INT_2_10_10_10_REV;
            case VertexLayout::VertexType::UNSIGNED_INT_2_10_10_10_REV: return sgf_core::VertexLayout::VertexType::UNSIGNED_INT_2_10_10_10_REV;
            case VertexLayout::VertexType::UNSIGNED_INT_10F_11F_11F_REV: return sgf_core::VertexLayout::VertexType::UNSIGNED_INT_10F_11F_11F_REV;
        }
    }

    uint32_t getSize(VertexLayout::VertexType type) {
        switch (type) {
            case VertexLayout::VertexType::BYTE: return sizeof(int8_t);
            case VertexLayout::VertexType::UNSIGNED_BYTE: return sizeof(uint8_t);
            case VertexLayout::VertexType::SHORT: return sizeof(int16_t);
            case VertexLayout::VertexType::UNSIGNED_SHORT: return sizeof(uint16_t);
            case VertexLayout::VertexType::INT: return sizeof(int32_t);
            case VertexLayout::VertexType::UNSIGNED_INT: return sizeof(uint32_t);
            case VertexLayout::VertexType::HALF_FLOAT: return sizeof(int16_t);
            case VertexLayout::VertexType::FLOAT: return sizeof(float);
            case VertexLayout::VertexType::DOUBLE: return sizeof(double);
            case VertexLayout::VertexType::INT_2_10_10_10_REV: return sizeof(int32_t);
            case VertexLayout::VertexType::UNSIGNED_INT_2_10_10_10_REV: return sizeof(uint32_t);
            case VertexLayout::VertexType::UNSIGNED_INT_10F_11F_11F_REV: return sizeof(uint32_t);
        }
    }

    struct VertexLayout::Impl {
        sgf_core::VertexLayout vertexLayout;
    };

    VertexLayout::VertexLayout():
        impl(std::make_shared<Impl>())
    {
    }

    VertexLayout::~VertexLayout() {
    }

    void VertexLayout::addAttribute(uint32_t index, uint32_t size, VertexType type, bool normalized, size_t offset) {
        impl->vertexLayout.addAttribute({
            .index = index,
            .size = size / getSize(type),
            .type = toCore(type),
            .normalized = normalized,
            .offset = offset
        });
    }

    const sgf_core::VertexLayout & VertexLayout::getCore() const {
        return impl->vertexLayout;
    }
}
