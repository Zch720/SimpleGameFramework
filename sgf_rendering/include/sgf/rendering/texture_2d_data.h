#pragma once

#include <cstdint>
#include <vector>

namespace sgf_core {
    enum TextureFormat {
        RED,
        RED_INTEGER,
        RG,
        RG_INTEGER,
        RGB,
        RGB_INTEGER,
        RGBA,
        RGBA_INTEGER,
        DEPTH_COMPONENT,
        DEPTH_STENCIL,
        LUMINANCE_ALPHA,
        LUMINANCE,
        ALPHA
    };

    enum TextureDataType {
        UNSIGNED_BYTE,
        BYTE,
        UNSIGNED_SHORT,
        SHORT,
        UNSIGNED_INT,
        INT,
        HALF_FLOAT,
        FLOAT,
        UNSIGNED_SHORT_5_6_5,
        UNSIGNED_SHORT_4_4_4_4,
        UNSIGNED_SHORT_5_5_5_1,
        UNSIGNED_INT_2_10_10_10_REV,
        UNSIGNED_INT_10F_11F_11F_REV,
        UNSIGNED_INT_5_9_9_9_REV,
        UNSIGNED_INT_24_8,
        FLOAT_32_UNSIGNED_INT_24_8_REV
    };
    
    struct Texture2DData {
        TextureFormat internalFormat;
        TextureFormat dataFormat;
        int width;
        int height;
        TextureDataType dataType;
        std::vector<uint8_t> data;
    };
}
