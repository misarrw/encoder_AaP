#pragma once
#include "..\VigenereCipher.h"

class VigenereOpenTextGamma : public VigenereCipher {
    protected:
    void creat_gamma() override;
    size_t get_len_key() const override {return 1;}
    public:
    VigenereOpenTextGamma(std::string text, int x) {
        param = x;
        text_numbers = text_in_numbers(text);
        check_key();
        creat_gamma();
        cipher();
    };
};
