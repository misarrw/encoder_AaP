#pragma once
#include <vector>


class SubFunction
{
public:
    static std::vector<int> text_in_numbers(const std::string& text);
    static std::string numbers_to_text(const std::vector<int>& nums);
    int extendedGCD(int a, int b, int& x, int& y);
    int modInverse(int a, int m);
    bool is_alpha(const std::string& str);
};