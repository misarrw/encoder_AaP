#pragma once
#include "../../globals.h"
#include "../BlockCipher.h"
#include <string>
#include <vector>


class HillCipher : public BlockCipher
{
public:
    HillCipher(std::vector<std::vector<int>> matrix) : BlockCipher(matrix) {}

    std::string hill(std::string& pretext, char& option) override;
};