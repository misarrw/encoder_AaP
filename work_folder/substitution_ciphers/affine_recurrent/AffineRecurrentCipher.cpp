#include <iostream>
#include <array>
#include <string>
#include "AffineRecurrentCipher.h"
#include "../../../globals.hpp"


std::array<int, 2> AffineRecurrentCipher::find_another_key(const std::array<int, 2>& key1, const std::array<int, 2>& key2, const std::string& text)
{
    std::array<int, 2> key3{(key1[0] * key2[0]) % ALPHABET_SIZE, (key1[1] + key2[1]) % ALPHABET_SIZE};
    return key3;
}