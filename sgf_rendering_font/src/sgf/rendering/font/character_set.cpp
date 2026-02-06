#include "../../../../include/sgf/rendering/font/character_set.h"
#include <sgf/utils/file/fileio.h>
#include <sgf/utils/file/utf8_decoder.h>
#include <sgf/utils/logger/log.h>

namespace sgf_font {
    const std::vector<CharacterSet::CharacterGroup> & CharacterSet::getGroups() const {
        return groups;
    }

    void CharacterSet::addGroup(const CharacterGroup & group) {
        groups.push_back(group);
    }

    void CharacterSet::addGroupWithFile(const std::string & filePath, const int size) {
        std::u32string utf8String = sgf_core::UTF8Decoder::decode(
            sgf_core::FileIO::read(filePath)
        );
        groups.push_back({
            size,
            { utf8String.begin(), utf8String.end() }
        });
    }
}
