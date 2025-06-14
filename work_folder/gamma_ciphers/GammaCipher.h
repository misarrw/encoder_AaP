#pragma once
#include <vector>
#include <string>
#include "../SubFunctions.h"
#include "globals.h"

class GammaCipher : public SubFunction
{
    protected:
    virtual std::vector<int> get_gamma() = 0;
    virtual const std::vector<int>& get_text() const = 0;
    virtual const int& get_param() = 0;
    virtual void add_char_gamma(std::vector<int>& gamma, int i) {return;}
    virtual void create_gamma() = 0;
    virtual void cipher();
    public:
    std::string ciphertext{};
    virtual ~GammaCipher() {}
};