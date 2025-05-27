#pragma once
#include <vector>
#include <string>
#include "..\GammaCipher.h"

class VigenereCipher : public GammaCipher{
    protected:
    std::string key;
    std::vector<int> key_numbers;
    size_t len_key;
    std::vector<int> check_key();
    VigenereCipher(std::string text, int x){
        text_numbers = text_in_numbers(text);
        x = x;
        check_key();
    }
    virtual ~VigenereCipher() {}
};