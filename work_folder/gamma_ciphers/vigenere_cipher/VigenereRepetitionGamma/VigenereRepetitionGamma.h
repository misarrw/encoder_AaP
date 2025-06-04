#pragma once
#include "..\VigenereCipher.h"

class VigenereRepetitionGamma : public VigenereCipher {
    protected:
    void creat_gamma() override;
    size_t get_len_key() const override {return text_numbers.size();}
    public:
    VigenereRepetitionGamma(std::string text, int x) {
        param = x;
        text_numbers = text_in_numbers(text);
        check_key();
        creat_gamma();
        cipher();
    };
};
