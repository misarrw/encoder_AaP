/**
 * \file
 * \brief Реализация метода создания гаммы в классе VigenereRepetitionGamma.
 */

#include "VigenereRepetitionGamma.h"
#include "../../../globals.h"
#include <iostream>
#include <cctype>

/**
 * \brief Создаёт гамму путём многократного повторения ключа по длине текста.
 */
void VigenereRepetitionGamma::create_gamma()
{
    const size_t len_text = text.size();
    const size_t len_key = key_numbers.size();

    std::string gamma_str;
    gamma_str.reserve(len_text);
    int j = 0;

    for (size_t i = 0; i < len_text; ++i) {
        char c = toupper(text[i]);
        if (ALPHABET.find(c) == std::string::npos) {
            gamma_str += "q";
            continue;
        }
        gamma_str += key[j % len_key];
        ++j;
    }

    gamma = text_in_numbers(gamma_str);
    return;
}
