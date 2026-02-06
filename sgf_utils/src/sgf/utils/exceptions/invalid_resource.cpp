#include "../../../../include/sgf/utils/exceptions/invalid_resource.h"

namespace sgf_core {
    InvalidResource::InvalidResource(const std::string & message) : message(message) {
    }

    const char* InvalidResource::what() const noexcept {
        return message.c_str();
    }
}
