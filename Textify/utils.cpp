#include "utils.hpp"

#include <fstream>

void Utils::glob (std::string & s_buffer, const std::string & s_name) {
    std::ifstream s_stream (s_name, std::ios::binary|std::ios::ate);
    if (s_stream.good ()) {
        const std::size_t s_length = s_stream.tellg ();
        s_stream.seekg (0u, std::ios::beg);
        s_buffer.clear ();
        s_buffer.resize (s_length);
        s_stream.read (const_cast<char*> (s_buffer.data ()), s_length);
    }
}

void Utils::glob_lines (std::string & s_buffer, const std::string & s_name) {
    std::ifstream s_stream (s_name, std::ios::binary);
    if (s_stream.good ()) {
        const std::size_t s_length = s_stream.tellg ();
        s_stream.seekg (0u, std::ios::beg);
        s_buffer.clear ();
        s_buffer.resize (s_length);
        std::string s_line;
        while (std::getline (s_stream, s_line)) {
            s_buffer.append (s_line);
        }
    }
}

void Utils::plop (const std::string & s_buffer, const std::string & s_name) {
    std::ofstream s_stream (s_name, std::ios::binary);
    if (s_stream.good ()) {
        s_stream.write (s_buffer.data (), s_buffer.length ());
    }
}
