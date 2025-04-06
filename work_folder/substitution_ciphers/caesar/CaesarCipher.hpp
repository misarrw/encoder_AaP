#pragma once
#include <string>

class CaesarCipher {
public:
    std::string caesar_encryption(const std::string& text, const std::string& key);

    std::string caesar_decryption(const std::string& cipher_text, const std::string& key);
};