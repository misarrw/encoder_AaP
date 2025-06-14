#pragma once
#include "../GammaCipher.h"
#include <iostream>


class VernameCipher: public GammaCipher {
    protected:
    void create_gamma() override;
    size_t len_text;
    std::vector<int> gamma;
    std::vector<int> get_gamma() override {return gamma;}
    std::vector<int> text_numbers;
    const std::vector<int>& get_text() const override {return text_numbers;}
    const int& get_param() override {return param;}
    int param;
    public:
    VernameCipher(std::string text, int x) {
        param = x;
        text_numbers = text_in_numbers(text);
        len_text = text.size();
        if (x == 1){
            create_gamma();
        } else {
            std::string gamma_text;
            std::cin >> gamma_text;
            gamma = text_in_numbers(gamma_text);
        }
        cipher();
    }
};