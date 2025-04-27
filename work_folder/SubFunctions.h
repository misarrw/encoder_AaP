#pragma once
#include <vector>
#include <string>

class SubFunction
{
    public:
        static std::vector<int> text_in_numbers(const std::string& text);
        static std::string numbers_to_text(const std::vector<int>& nums);
};