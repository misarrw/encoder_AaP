#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "SubFunctions.hpp"

extern const std::string ALPHABET;

// Tests for Subfunction: Text into Numbers
TEST_CASE("Encoding tests") {
    SubFunction encoder;
    
    SUBCASE("Space encoding") {
        CHECK(encoder.text_in_numbers(" ") == std::vector<int>{0, 0});
    }
    
    SUBCASE("Letters encoding") {
        // A=1, B=2, C=3, D=4
        CHECK(encoder.text_in_numbers("ABCD") == std::vector<int>{1, 2, 3, 4});
    }
    
    SUBCASE("Mixed input") {
        CHECK(encoder.text_in_numbers("A B") == std::vector<int>{1, 0, 0, 2});  
}
    SUBCASE("Sentence encoding") {
        CHECK(encoder.text_in_numbers("Hello, world!") == std::vector<int>{8, 5, 12, 12, 15, 103, 0, 0, 23, 15, 18, 12, 4, 101});  

    }
}