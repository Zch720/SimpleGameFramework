#pragma once

#include <string>

namespace sgf_core {
    class FileIO {
    public:
        static std::string read(const std::string & filePath);
        static void write(const std::string & filePath, const std::string & content);
    };
}
