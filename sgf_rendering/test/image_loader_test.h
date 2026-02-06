#include <gtest/gtest.h>
#include <sgf/utils/exceptions/initialization_failed.h>
#include <sgf/utils/exceptions/invalid_resource.h>
#include "./utils.h"
#include "../include/sgf/rendering/image_loader.h"

using namespace sgf_core;

class ImageLoaderSuite: public ::testing::Test {
protected:
    void SetUp() override {
        sgf_test::createOpenGLContext();
    }

    void TearDown() override {
        sgf_test::OpenGLContextTerminate();
    }
};

TEST_F(ImageLoaderSuite, LoadPngImage) {
    ASSERT_NO_THROW(ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.png"));
}

TEST_F(ImageLoaderSuite, PngImageLoadedWithCorrectInfo) {
    Texture2DData data = ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.png");
    ASSERT_EQ(225, data.width);
    ASSERT_EQ(225, data.height);
    ASSERT_EQ(TextureFormat::RGBA, data.internalFormat);
    ASSERT_EQ(TextureFormat::RGBA, data.dataFormat);
    ASSERT_EQ(TextureDataType::UNSIGNED_BYTE, data.dataType);
}

TEST_F(ImageLoaderSuite, LoadJpgImage) {
    ASSERT_NO_THROW(ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.jpg"));
}

TEST_F(ImageLoaderSuite, JpgImageLoadedWithCorrectInfo) {
    Texture2DData data = ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.jpg");
    ASSERT_EQ(225, data.width);
    ASSERT_EQ(225, data.width);
}

TEST_F(ImageLoaderSuite, LoadBmpImage) {
    ASSERT_NO_THROW(ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.bmp"));
}

TEST_F(ImageLoaderSuite, BmpImageLoadedWithCorrectInfo) {
    Texture2DData data = ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.bmp");
    ASSERT_EQ(225, data.width);
    ASSERT_EQ(225, data.height);
}

TEST_F(ImageLoaderSuite, LoadTifImage) {
    ASSERT_THROW_MESSAGE(ImageLoader::loadImage(TEST_RESOURCES_DIR"/image.tif"),
        sgf_core::InvalidResource,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/image.tif. Invalid texture type.");
}

TEST_F(ImageLoaderSuite, LoadImageNotExist) {
    ASSERT_THROW_MESSAGE(ImageLoader::loadImage(TEST_RESOURCES_DIR"/not_exist.png"),
        sgf_core::InitializationFailed,
        "Load texture file at '" TEST_RESOURCES_DIR "/not_exist.png' failed");
}