#include "../../../internal_include/sgf/rendering/texture_enum_mapper.h"
#include <glad/gl.h>

namespace sgf_core {
    std::unordered_map<TextureFormat, uint32_t> TextureEnumMapper::formatMapper = {
        { RED, GL_RED },
        { RED_INTEGER, GL_RED_INTEGER },
        { RG, GL_RG },
        { RG_INTEGER, GL_RG_INTEGER },
        { RGB, GL_RGB },
        { RGB_INTEGER, GL_RGB_INTEGER },
        { RGBA, GL_RGBA },
        { RGBA_INTEGER, GL_RGBA_INTEGER },
        { DEPTH_COMPONENT, GL_DEPTH_COMPONENT },
        { DEPTH_STENCIL, GL_DEPTH_STENCIL },
        { LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA },
        { LUMINANCE, GL_LUMINANCE },
        { ALPHA, GL_ALPHA },
    };

    std::unordered_map<TextureDataType, uint32_t> TextureEnumMapper::dataTypeMapper = {
        { UNSIGNED_BYTE, GL_UNSIGNED_BYTE },
        { BYTE, GL_BYTE },
        { UNSIGNED_SHORT, GL_UNSIGNED_SHORT },
        { SHORT, GL_SHORT },
        { UNSIGNED_INT, GL_UNSIGNED_INT },
        { INT, GL_INT },
        { HALF_FLOAT, GL_HALF_FLOAT },
        { FLOAT, GL_FLOAT },
        { UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5 },
        { UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4 },
        { UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_5_5_5_1 },
        { UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV },
        { UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_10F_11F_11F_REV },
        { UNSIGNED_INT_5_9_9_9_REV, GL_UNSIGNED_INT_5_9_9_9_REV },
        { UNSIGNED_INT_24_8, GL_UNSIGNED_INT_24_8 },
        { FLOAT_32_UNSIGNED_INT_24_8_REV, GL_FLOAT_32_UNSIGNED_INT_24_8_REV },
    };

    uint32_t TextureEnumMapper::SgfTextureFormatToGL(TextureFormat format) {
        return formatMapper[format];
    }

    uint32_t TextureEnumMapper::SgfTextureDataTypeToGL(TextureDataType type) {
        return dataTypeMapper[type];
    }
}
