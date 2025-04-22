#pragma once
#include <string>
#include "../SubstitutionCipher.hpp"


class CaesarCipher : public SubstitutionCipher {
public:
    std::string caesar_encryption(const std::string& text, const std::string& key);

    std::string caesar_decryption(const std::string& cipher_text, const std::string& key);
};