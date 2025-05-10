#pragma once
#include <string>
#include "../SubstitutionCipher.h"
#include <unordered_set>
#include "globals.h"


class CaesarCipher : public SubstitutionCipher {
private:
    std::string key;

public:
    CaesarCipher(std::string k) : key(k) 
    {
        std::unordered_set<char> key_set;
        for (char symbol: key) {
            key_set.insert(symbol);
        }
        if (key_set.size() != ALPHABET_SIZE) {
            throw std::length_error("\nYour key is too short or incorrect. Check the tip and try again");
        }
    }
    std::string caesar_encryption(const std::string& text);
    std::string caesar_decryption(const std::string& cipher_text);
};