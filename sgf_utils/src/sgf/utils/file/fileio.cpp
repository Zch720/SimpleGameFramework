#include "../../../../include/sgf/utils/file/fileio.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace sgf_core {
    std::string FileIO::read(const std::string & filePath) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file '" + filePath + "'");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        file.close();

        return content;
    }

    void FileIO::write(const std::string & filePath, const std::string & content) {
        std::ofstream file(filePath);
        file << content;
        file.close();
    }
}
