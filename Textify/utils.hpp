#pragma once

#include <string>

struct Utils {
    static void glob (std::string& s_buffer, const std::string& s_name);
    static void glob_lines (std::string& s_buffer, const std::string& s_name);
    static void plop (const std::string& s_buffer, const std::string& s_name);
};

