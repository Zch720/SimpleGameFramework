#include "../../../../include/sgf/utils/file/utf8_decoder.h"
#include <codecvt>
#include <locale>

namespace sgf_core {
    std::u32string UTF8Decoder::decode(const std::string & rawStr) {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convertor;
        return convertor.from_bytes(rawStr);
    }
}
