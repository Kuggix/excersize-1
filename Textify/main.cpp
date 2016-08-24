#include <iostream>
#include <cassert>

#include "base64.hpp"
#include "utils.hpp"

int main (int, char**) {    
    {
        std::string o0, o1;
        Base64::encode (o0, "any carnal pleasure.");
        assert (o0 == "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
        Base64::decode (o1, o0);
        assert (o1 == "any carnal pleasure.");


        Base64::encode (o0, "any carnal pleasure");
        assert (o0 == "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
        Base64::decode (o1, o0);
        assert (o1 == "any carnal pleasure");


        Base64::encode (o0, "any carnal pleasur");
        assert (o0 == "YW55IGNhcm5hbCBwbGVhc3Vy");
        Base64::decode (o1, o0);
        assert (o1 == "any carnal pleasur");


        Base64::encode (o0, "any carnal pleasu");
        assert (o0 == "YW55IGNhcm5hbCBwbGVhc3U=");
        Base64::decode (o1, o0);
        assert (o1 == "any carnal pleasu");


        Base64::encode (o0, "any carnal pleas");
        assert (o0 == "YW55IGNhcm5hbCBwbGVhcw==");
        Base64::decode (o1, o0);
        assert (o1 == "any carnal pleas");
    }
    
    {
        std::string s_buffer, s_output;
        Utils::glob (s_buffer, "test3");        
        Base64::encode (s_output, s_buffer);        
        Utils::plop (s_output, "test3.base64");
        assert (std::system ("fc test3.base64 test3.ref") == 0);
        Base64::decode (s_buffer, s_output);
        Utils::plop (s_buffer, "test3.orig");        
        assert (std::system ("fc /B test3 test3.orig") == 0);
        
    }

    {
        std::string s_buffer, s_output;
        Utils::glob (s_buffer, "test2");
        Base64::encode (s_output, s_buffer);
        Utils::plop (s_output, "test2.base64");
        assert (std::system ("fc test2.base64 test2.ref") == 0);
        Base64::decode (s_buffer, s_output);
        Utils::plop (s_buffer, "test2.orig");
        assert (std::system ("fc /B test2 test2.orig") == 0);
    }

    {
        std::string s_buffer, s_output;
        Utils::glob (s_buffer, "test1");
        Base64::encode (s_output, s_buffer);
        Utils::plop (s_output, "test1.base64");
        assert (std::system ("fc test1.base64 test1.ref") == 0);
        Base64::decode (s_buffer, s_output);
        Utils::plop (s_buffer, "test1.orig");
        assert (std::system ("fc /B test1 test1.orig") == 0);
    }
    return 0;
}