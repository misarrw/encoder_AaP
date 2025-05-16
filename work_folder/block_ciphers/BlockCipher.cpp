#pragma once
#include "BlockCipher.h"
#include "globals.h"
#include <string>


std::vector<std::vector<int>> BlockCipher::text_into_numbers_ngrammas(std::string& text)
{
    std::vector<std::string> ngrammas_list;
    size_t key_size = key_vec.size();
    size_t text_size = text.size();

    while (text.size() % key_size != 0) {
        text += 'x';
    }

    for (size_t i = 0; i < text.size(); i += key_size) {
        ngrammas_list.push_back(text.substr(i, key_size));
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

bool BlockCipher::check_key(size_t key_space, size_t block_size)
{
    if (key_space != block_size * block_size) {
        return false;
    }
    return true;
}
