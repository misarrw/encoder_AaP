#pragma once
#include "../../VigenereCipher.h"


class RepetitionGamma : public VigenereCipher
{
public: 
    std::vector<int> repgamma(const std::string& key, std::vector<int>& text_numbers);
};