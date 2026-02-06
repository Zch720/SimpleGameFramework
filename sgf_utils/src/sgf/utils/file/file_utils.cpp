#include "../../../../include/sgf/utils/file/file_utils.h"
#include <filesystem>

namespace sgf_core {
    std::string getFileName(const std::string & filePath) {
        return std::filesystem::path(filePath).filename();
    }
}
