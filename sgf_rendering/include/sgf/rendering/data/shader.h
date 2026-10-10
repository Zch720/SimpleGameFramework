#pragma once

#include <string>

#include "sgf/utils/manager/define.h"
#include "sgf/utils/manager/resource.h"

namespace sgf::rendering {
    class Shader: public sgf::utils::Resource {
        FRIEND_RESOURCE_MANAGER;

    private:
        std::string m_sVertexShaderSource = "";
        std::string m_sFragmentShaderSource = "";

    public:
        struct Construct {
            std::string sVertexShaderSource;
            std::string sFragmentShaderSource;
        };

    protected:
        Shader(
            const Construct& construct
        ):
            m_sVertexShaderSource(construct.sVertexShaderSource),
            m_sFragmentShaderSource(construct.sFragmentShaderSource)
        {
        }

    public:
        inline static std::string_view getTypeName() {
            return "Shader";
        }

        inline const std::string& getVertexShaderSource() const {
            return m_sVertexShaderSource;
        }

        inline const std::string& getFragmentShaderSource() const {
            return m_sFragmentShaderSource;
        }
    };
}
