#pragma once

#include <cstddef>
#include <string>

struct Base64 {
    static bool is_valid_char (std::uint8_t s_char);

    static std::uint8_t decode_one (std::uint8_t s_char);
    static char encode_one (std::uint8_t c);

    static void encode (std::string& s_output, const std::string& s_input);
    static void decode (std::string& s_output, const std::string& s_input);
};


