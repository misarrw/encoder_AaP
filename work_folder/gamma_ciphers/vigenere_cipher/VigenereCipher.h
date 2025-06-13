#pragma once
#include <vector>
#include <string>
#include "../GammaCipher.h"

class VigenereCipher : public GammaCipher{
    protected:
    std::string key;
    std::vector<int> key_numbers;
    std::vector<int> gamma;
    std::vector<int> text_numbers;
    virtual size_t get_len_key() const {return 0;}
    std::vector<int> get_gamma() override {return gamma;}
    const int& get_param() override {return param;}
    const std::vector<int>& get_text() const override {return text_numbers;}
    int param;
    virtual void check_key();
    VigenereCipher() {}
    virtual ~VigenereCipher() {}
};