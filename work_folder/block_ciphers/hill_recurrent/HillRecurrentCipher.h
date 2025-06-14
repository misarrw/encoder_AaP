#pragma once
#include "../../globals.h"
#include "../BlockCipher.h"
#include <string>
#include <vector>


class HillRecurrentCipher : public BlockCipher {
    protected:
        std::vector<std::vector<int>> key1;
        std::vector<std::vector<int>> key2;
    public:
        HillRecurrentCipher(const std::vector<std::vector<int>>& key1,
                                       const std::vector<std::vector<int>>& key2): BlockCipher(key1), key1(key1), key2(key2) {};
        std::vector<std::vector<int>> generate_next_key(std::vector<std::vector<int>> key1, std::vector<std::vector<int>> key2);
        std::string hill(std::string& pretext, char& option) override;
};

