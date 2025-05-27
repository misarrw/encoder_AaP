#pragma once
#include "../GammaCipher.h"
#include <iostream>


class VernameCipher: public GammaCipher {
    protected:
    void creat_gamma() override;
    size_t len_text;
    public:
    VernameCipher(std::string text, int x) {
        text_numbers = text_in_numbers(text);
        len_text = text.size();
        if (x == 1){
            creat_gamma();
        } else {
            std::string gamma_text;
            std::cin >> gamma_text;
            gamma = text_in_numbers(gamma_text);
        }
        cipher();
    }
};