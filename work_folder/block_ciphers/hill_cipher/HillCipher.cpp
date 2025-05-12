#pragma once
#include "HillCipher.h"
#include <string>
#include <vector>
#include "../BlockCipher.h"
#include "globals.h"
#include <cctype>
#include <algorithm>


std::string HillCipher::hill(std::string& pretext, int& option)
{
    std::string text;
    for (char symbol: text) {
        if (!std::count(SYMBOLS.begin(), SYMBOLS.end(), symbol)) {
            text += symbol;
        }
    }
    std::vector<std::vector<int>> text_ngrammas_numbers = text_into_numbers_ngrammas(pretext);
    std::vector<std::vector<int>> ciphertext_ngrammas_numbers;
    std::vector<int> ciphertext_ngramma;
    int letter = 0;
    size_t key_size = key_vec.size();
    for (std::vector<int> text_ngramma: text_ngrammas_numbers) {
        for (size_t i = 0; i < key_size; i++) {
            for (size_t j = 0; j < key_size; i++) {
                letter += key_vec[i][j] * text_ngramma[j];
            }
            ciphertext_ngramma.push_back(letter % ALPHABET_SIZE);
            letter = 0;
        }
        ciphertext_ngrammas_numbers.push_back(ciphertext_ngramma);
        ciphertext_ngramma.clear();
    }

    std::string ciphertext;
    for (std::vector<int> ngramma_numbers: ciphertext_ngrammas_numbers) {
        for (int number: ngramma_numbers) {
            ciphertext += static_cast<char>(ALPHABET[number]);
        }
    }
    for (auto& c : ciphertext) {
        c = std::toupper(c);
    }
    return ciphertext;
}
