#pragma once

#include <stdint.h>
#include <sgf/utils/resource.h>
#include "./resource_type.h"
#include "./texture_2d_data.h"
#include "./texture_2d_id.h"

namespace sgf_core {
    class UnsafeGLContext;

    class Texture2D: public Resource<Texture2D, Texture2DId> {
    public:
        static const std::string TypeName;
        struct Construct {
            ResourceType type = ResourceType::STATIC;
            const Texture2DData & data;
        };

        Texture2D(const Id & id, const Construct & constructParameter);
        ~Texture2D();

        int getWidth() const;
        int getHeight() const;

        void bind() const;

        void updateData(const Texture2DData & data);

    private:
        friend UnsafeGLContext;

        ResourceType type;
        
        Texture2DData data;

        uint32_t textureHandle;
    };
}
