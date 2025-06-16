/**
 * \file
 * \brief Реализация метода создания гаммы в классе VigenereOpenTextGamma.
 */

#include "../../../globals.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "VigenereOpenTextGamma.h"

/**
 * \brief Формирует гамму из ключа и открытого текста.
 */
void VigenereOpenTextGamma::create_gamma() 
{
    gamma.push_back(key_numbers[0]);

    std::string gamma_str{};
    for (int i = 0; i < (text.size() - 1); i++) {
        char c = toupper(text[i]);
        int index = ALPHABET.find(c);
        if (index == std::string::npos) {
            gamma_str += "q";
            continue;
        }
        gamma_str += text[i];
    }

    std::vector<int> gamma_numbers{ text_in_numbers(gamma_str) };
    gamma.insert(gamma.end(), gamma_numbers.begin(), gamma_numbers.end());
}
