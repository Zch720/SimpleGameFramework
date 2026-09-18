#pragma once

#include <exception>
#include <string>

namespace sgf::utils {
    class ResourceNotFound: public std::exception {
    private:
        std::string m_sMessage;

    public:
        ResourceNotFound(
            const std::string& sMessage
        ):
            m_sMessage(sMessage)
        {
        }

        virtual inline const char* what() const noexcept override {
            return m_sMessage.c_str();
        }
    };
}
