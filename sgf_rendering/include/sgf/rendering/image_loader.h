#pragma once

#include <string>
#include "./texture_2d_data.h"

namespace sgf_core {
    class ImageLoader {
    public:
        static Texture2DData loadImage(const std::string & imagePath);

    private:
        static void checkIsValidType(const std::string & imagePath);
    };
}
