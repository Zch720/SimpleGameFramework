#include "../../../include/sgf/rendering/image_loader.h"
#include <iterator>
#include <regex>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <sgf/utils/exceptions/initialization_failed.h>
#include <sgf/utils/exceptions/invalid_resource.h>
#include <sgf/utils/logger/log.h>

namespace sgf_core {
    Texture2DData ImageLoader::loadImage(const std::string &imagePath) {
        checkIsValidType(imagePath);
        
        Texture2DData result;

        int channels;
        uint8_t * data = stbi_load(imagePath.c_str(), &result.width, &result.height, &channels, STBI_rgb_alpha);
        size_t dataSize = result.width * result.height * 4;
        if (data == nullptr) {
            SGF_LOG_ERROR("Load texture file at '{}' failed", imagePath);
            throw InitializationFailed("Load texture file at '" + imagePath + "' failed");
        }

        result.internalFormat = TextureFormat::RGBA;
        result.dataFormat = TextureFormat::RGBA;
        result.dataType = TextureDataType::UNSIGNED_BYTE;

        std::copy(data, data + dataSize, std::back_inserter(result.data));
        stbi_image_free(data);
        return result;
    };

    void ImageLoader::checkIsValidType(const std::string & imagePath) {
        std::regex textureRegex(".*\\.(bmp|jpg|png)$");
        if (!std::regex_search(imagePath.begin(), imagePath.end(), textureRegex)) {
            SGF_LOG_ERROR("Unable to load texture file: {}. Invalid texture type.", imagePath);
            throw InvalidResource("Unable to load texture file: " + imagePath + ". Invalid texture type.");
        }
    }
}
