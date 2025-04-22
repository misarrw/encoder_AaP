# include "OpentextGamma.h"
# include "../../../../globals.hpp"
# include <iostream>
# include <vector>
# include <string>
# include <cctype>


std::vector<int> OpentextGamma::opentext(const std::string& key, std::vector<int>& text_numbers, int option)
{
    std::vector<int> gamma{};
    for (char symbol: key)  { // надо будет учесть регистр букв в ключе
        gamma.push_back(ALPHABET.find(symbol));
        int index = 0;
        int len_text_numbers = text_numbers.size();
        while (gamma.size() < len_text_numbers) {
            if (option == 1) {
                gamma.push_back(text_numbers[index]);
            }
            else {
                gamma.push_back((text_numbers[index] - gamma[index]) % ALPHABET_SIZE);
            }
            index++;
        }
    }
    return gamma;
}