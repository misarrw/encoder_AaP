#pragma once
#include "BlockCipher.h"
#include "globals.h"
#include <string>

std::vector<std::vector<int>> BlockCipher::text_into_numbers_ngrammas(std::string& text, std::vector<std::vector<int>>& key)
{
    std::vector<std::string> ngrammas_list;
    size_t key_size = key.size();
    while (text.size() % key_size != 0) {
        text += 'x';
    }
    size_t text_size = text.size();
    for (size_t index = 1; index < text_size; index++) {
        if ((index + 1) % key[0].size() == 0) {
            size_t begin = index + 1 - key[0].size();
            size_t length = key[0].size();
            ngrammas_list.push_back(text.substr(begin, length));
        }
    }
    std::vector<int> ngramma_numbers;
    std::vector<std::vector<int>> ngrammas_numbers;
    for (std::string ngramma: ngrammas_list) {
        for (char letter: ngramma) {
            ngramma_numbers.push_back(ALPHABET.find(letter));
        }
        ngrammas_numbers.push_back(ngramma_numbers);
        ngramma_numbers.clear();
    }
    return ngrammas_numbers;
}