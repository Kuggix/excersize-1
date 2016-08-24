#pragma once

#include <cstddef>
#include <string>

struct Base64 {
    static void encode (std::string& s_output, const std::string& s_input);
    static void decode (std::string& s_output, const std::string& s_input);
};


