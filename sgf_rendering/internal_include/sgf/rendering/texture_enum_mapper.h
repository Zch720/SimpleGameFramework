#pragma once

#include <unordered_map>
#include "../../../include/sgf/rendering/texture_2d_data.h"

namespace sgf_core {
    class TextureEnumMapper {
    public:
        static uint32_t SgfTextureFormatToGL(TextureFormat format);
        static uint32_t SgfTextureDataTypeToGL(TextureDataType type);

    private:
        static std::unordered_map<TextureFormat, uint32_t> formatMapper; 
        static std::unordered_map<TextureDataType, uint32_t> dataTypeMapper; 
    };
}
