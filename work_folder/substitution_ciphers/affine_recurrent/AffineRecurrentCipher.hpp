#pragma once
#include <array>
#include <string>

class AffineRecurrentCipher {
    public:
        std::string encryption (const std::string& text, const std::array<int, 2>& key1, const std::array<int, 2>& key2);
        std::vector<std::array<int, 2>> all_keys(const std::array<int, 2>& key1, const std::array<int, 2>& key2, const std::string& text);
        std::vector<std::array<int, 2>> decryption_keys(const std::vector<std::array<int, 2>>& encryption_keys);
        std::string decryption(const std::string& ciphertext, const std::array<int, 2>& key1, const std::array<int, 2>& key2);

};