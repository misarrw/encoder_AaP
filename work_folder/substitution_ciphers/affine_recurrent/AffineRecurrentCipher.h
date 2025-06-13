#pragma once
#include <array>
#include <string>
#include <numeric>
#include "../SubstitutionCipher.h"
#include "globals.h"

class AffineRecurrentCipher{
    protected:
        std::array<int, 2> key1;
        std::array<int, 2> key2;
        std::array<int, 2> find_another_key(const std::array<int, 2>& key1, const std::array<int, 2>& key2);
    public:
        AffineRecurrentCipher(const std::array<int, 2>& key1, const std::array<int, 2>& key2): key1(key1), key2(key2) 
        {
            is_valid_key(key1);
            is_valid_key(key2);
        };
        bool is_valid_key(const std::array<int, 2>& key) {
            if (key[0] <= 0 || key[0] >= ALPHABET_SIZE) {
                std::cerr << "Alpha must be between 1 and " << ALPHABET_SIZE-1 << "\n";
                return false;
            }
            if (std::gcd(key[0], ALPHABET_SIZE) != 1) {
                std::cerr << "Alpha must be coprime with " << ALPHABET_SIZE << "\n";
                return false;
            }

            if (key[1] < 0 || key[1] >= ALPHABET_SIZE) {
                std::cerr << "Beta must be between 0 and " << ALPHABET_SIZE-1 << "\n";
                return false;
            }

            return true;
        }
        std::string cipher (const std::string& text, const int choice);
};