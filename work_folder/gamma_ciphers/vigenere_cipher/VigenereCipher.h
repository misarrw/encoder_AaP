#pragma once
#include <vector>
#include <string>
#include "..\GammaCipher.h"

class VigenereCipher : public GammaCipher{
    protected:
    std::vector<int> gamma;
    std::vector<int> check_key();
    void cipher() override;
    void add_char_gamma(int i);
    VigenereCipher(std::string text, bool flag){
        text_numbers = text_in_numbers(text);
        flag = flag;
        check_key();
        creat_gamma();
        cipher();
    }
    virtual ~VigenereCipher() {}
};