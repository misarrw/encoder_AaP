#pragma once
#include <vector>
#include <string>
#include "..\SubFunctions.h"
#include "globals.h"

class GammaCipher : public SubFunction
{
    protected:
    std::vector<int> text_numbers;
    std::vector<int> gamma;
    int x;
    void add_char_gamma(int i) {}
    virtual void creat_gamma() = 0;
    public:
    std::string cipher();
    virtual ~GammaCipher() {}
};