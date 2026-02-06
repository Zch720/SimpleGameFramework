#pragma once

#include <string>
#include <vector>
#include "./character.h"

namespace sgf_font {
    class CharacterSet {
    public:
        struct CharacterGroup {
            int size;
            std::vector<CharacterCode> characters;
        };

    private:
        std::vector<CharacterGroup> groups;

    public:
        const std::vector<CharacterGroup> & getGroups() const;

        void addGroup(const CharacterGroup & group);
        void addGroupWithFile(const std::string & filePath, const int size);
    };
}
