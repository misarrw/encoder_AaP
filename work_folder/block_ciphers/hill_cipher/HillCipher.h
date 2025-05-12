#pragma once
#include "../../globals.h"
#include "../BlockCipher.h"
#include <string>
#include <vector>


class HillCipher : public BlockCipher
{
public:
    std::string hill(std::string& pretext, int& option);
};