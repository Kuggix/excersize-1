#include "base64.hpp"

#include <cassert>

bool Base64::is_valid_char (std::uint8_t s_char) {
    return (s_char >= 'A' && s_char <= 'Z')
        || (s_char >= 'a' && s_char <= 'z')
        || (s_char >= '0' && s_char <= '9')
        || (s_char == '+')
        || (s_char == '/')
        || (s_char == '=');
}

std::uint8_t Base64::decode_one (std::uint8_t s_char) {
    assert (is_valid_char (s_char) == true);
    if (s_char >= 'A' && s_char <= 'Z')
        return s_char - 'A';
    if (s_char >= 'a' && s_char <= 'z')
        return s_char - 'a' + 26;
    if (s_char >= '0' && s_char <= '9')
        return s_char - '0' + 2*26;
    if (s_char == '+') return 62;
    if (s_char == '/') return 63;
    if (s_char == '=') return 0;
    return 0xff;
}

char Base64::encode_one (std::uint8_t c) {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/"
        [c & 0x3f];
}

void Base64::encode (std::string & s_output, const std::string & s_input) {

    s_output.clear ();

    std::uint32_t s_counter = 0u;

    auto i = 0u;
    while (i < s_input.length ()) {
        auto s_buffer = 0u;
        auto s_bytes_out = 1u;
        while (s_bytes_out < 4 && i < s_input.length ()) {
            s_buffer = (s_buffer << 8u) | (std::uint8_t)s_input [i++];
            ++s_bytes_out;
        }

        s_buffer <<= ((4u - s_bytes_out) * 8u);

        std::uint8_t s_temp [4] = {
            std::uint8_t (encode_one ((s_buffer >> 18u) & 0x3F)),
            std::uint8_t (encode_one ((s_buffer >> 12u) & 0x3F)),
            std::uint8_t (s_bytes_out >= 3 ? encode_one ((s_buffer >> 6u) & 0x3F) : '='),
            std::uint8_t (s_bytes_out >= 4 ? encode_one ((s_buffer >> 0u) & 0x3F) : '=')
        };

        s_output.append (reinterpret_cast<const char*> (s_temp), 4u);
        s_counter += 4u;
        if (s_counter >= 64u) {
            s_counter = 0u;
            s_output.append ("\n");
        }
    }
}

void Base64::decode (std::string & s_output, const std::string & s_input) {

    s_output.clear ();

    auto i = 0u;
    while (i < s_input.length ()) {
        std::uint8_t s_temp [3u];
        auto s_bytes_in = 0u;
        auto s_bytes_out = 3u;
        auto s_buffer = 0u;
        while (s_bytes_in < 4u) {
            if (s_input.length () - i + s_bytes_in < 4u) {
                return;
            }
            auto s_char = s_input [i++];
            if (is_valid_char (s_char)) {
                if (s_char == '=') {
                    --s_bytes_out;
                }
                s_buffer = (s_buffer << 6u) | decode_one (s_char);
                ++s_bytes_in;
            }
        }

        s_temp [0u] = (s_buffer >> 16u) & 0xffu;
        s_temp [1u] = (s_buffer >> 8u) & 0xffu;
        s_temp [2u] = s_buffer & 0xffu;

        s_output.append (reinterpret_cast<const char*>(&s_temp [0]), s_bytes_out);

    }

}
