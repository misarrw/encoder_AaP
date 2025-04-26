#pragma once
#include "../BlockCipher.h"
#include <string>
#include <vector>


class HillCipher : public BlockCipher
{
    std::string hill(std::string& text, std::vector<std::vector<int>>& key, int& option);
};