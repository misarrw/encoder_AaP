#pragma once
#include "BlockCipher.h"
#include "globals.h"
#include <string>


std::vector<std::vector<int>> BlockCipher::text_into_numbers_ngrammas(std::string& text)
{
    std::vector<std::string> ngrammas_list;
    key_size = key_vec.size();
    while (text.size() % key_size != 0) {
        text += 'x';
    }
    size_t text_size = text.size();
    for (size_t index = 1; index < text_size; index++) {
        if ((index + 1) % key_vec[0].size() == 0) {
            size_t begin = index + 1 - key_vec[0].size();
            size_t length = key_vec[0].size();
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

int BlockCipher::extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int BlockCipher::modInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);
    
    if (gcd != 1) {
        return -1; 
    } else {
        return (x % m + m) % m;
    }
}

bool BlockCipher::check_key(size_t block_size)
{
    if (key_size != block_size * block_size){
        return false;
    }
    return true;
}
