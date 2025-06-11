#pragma once
#include "..\VigenereCipher.h"

class VigenereCipherTextGamma : public VigenereCipher {
    protected:
    size_t get_len_key() const override {return 1;}
    void creat_gamma() override;
    void add_char_gamma(std::vector<int>& gamma_cipher, int i);
    public:
    VigenereCipherTextGamma(std::string text, int x) {
        param = x;
        text_numbers = text_in_numbers(text);
        check_key();
        creat_gamma();
        cipher();
    };
};
