#pragma once
#include <string>
#include "../SubstitutionCipher.h"
#include <unordered_set>
#include "../../globals.h"


class CaesarCipher : public SubstitutionCipher {
private:
    std::string key;
    void check_caesar_key(std::unordered_set<char> key_set);

public:
    CaesarCipher(std::string k) : key(k) 
    {
        std::unordered_set<char> key_set;
        for (char symbol: key) {
            key_set.insert(symbol);
        }
        try {
            check_caesar_key(key_set);
        }
        catch (const InvalidInputError& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    std::string caesar_encryption(const std::string& text);
    std::string caesar_decryption(const std::string& cipher_text);
};