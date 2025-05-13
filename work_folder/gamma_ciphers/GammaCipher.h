#pragma once
#include <vector>
#include <string>
#include "..\SubFunctions.h"

class GammaCipher : public SubFunction
{
    protected:
    std::vector<int> text_numbers;
    std::string key;
    std::vector<int> key_numbers;
    bool flag;
    size_t len_key;
    virtual void creat_gamma() = 0;
    virtual void cipher() = 0;
    virtual ~GammaCipher() {}
};