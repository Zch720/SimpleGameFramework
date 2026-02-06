#pragma once

#include <string>

namespace sgf_core {
    class UTF8Decoder {
    public:
        static std::u32string decode(const std::string & rawStr);
    };
}
