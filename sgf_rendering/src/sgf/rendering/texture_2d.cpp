#include "../../../include/sgf/rendering/texture_2d.h"
#include <glad/gl.h>
#include <sgf/utils/exceptions/invalid_state.h>
#include "../../../internal_include/sgf/rendering/texture_enum_mapper.h"

namespace sgf_core {
    const std::string Texture2DTag::TypeName = "Texture2D";
    const std::string Texture2D::TypeName = "Texture2D";

    Texture2D::Texture2D(const Id & id, const Construct & constructParameter):
        type(constructParameter.type),
        data(constructParameter.data)
    {
        this->id = id;

        glGenTextures(1, &textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            TextureEnumMapper::SgfTextureFormatToGL(data.internalFormat),
            data.width, data.height,
            0,
            TextureEnumMapper::SgfTextureFormatToGL(data.dataFormat),
            TextureEnumMapper::SgfTextureDataTypeToGL(data.dataType),
            data.data.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture2D::~Texture2D() {
        if (textureHandle != 0) {
            glDeleteTextures(1, &textureHandle);
        }
    }

    int Texture2D::getWidth() const {
        return data.width;
    }

    int Texture2D::getHeight() const {
        return data.height;
    }

    void Texture2D::bind() const {
        glBindTexture(GL_TEXTURE_2D, textureHandle);
    }

    void Texture2D::updateData(const Texture2DData & data) {
        if (type == ResourceType::STATIC) {
            throw InvalidState("Try to update " + getTypeName() + " data with id " + id.toString() + ", but it type is set to static");
        }

        glBindTexture(GL_TEXTURE_2D, textureHandle);
        if (data.width == this->data.width && data.height == this->data.height) {
            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                0, 0,
                data.width, data.height,
                TextureEnumMapper::SgfTextureFormatToGL(data.dataFormat),
                TextureEnumMapper::SgfTextureDataTypeToGL(data.dataType),
                data.data.data()
            );
        } else {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                TextureEnumMapper::SgfTextureFormatToGL(data.internalFormat),
                data.width, data.height,
                0,
                TextureEnumMapper::SgfTextureFormatToGL(data.dataFormat),
                TextureEnumMapper::SgfTextureDataTypeToGL(data.dataType),
                data.data.data());
        }

        this->data = data;
    }
}
