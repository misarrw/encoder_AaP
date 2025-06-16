/**
 * \file
 * \brief Реализация метода HillCipher::hill — классического блочного шифра Хилла.
 */

#include "HillCipher.h"
#include <string>
#include <vector>
#include "../BlockCipher.h"
#include "globals.h"
#include <cctype>
#include <algorithm>

/**
 * \brief Шифрует или дешифрует текст методом Хилла.
 * \param pretext Входной текст.
 * \param option '1' — шифрование, '2' — дешифрование.
 * \return Результирующий текст.
 */
std::string HillCipher::hill(std::string& pretext, char& option)
{
    if (option == '2') {
        key_vec = find_inverse_matrix(key_vec);
    }
    std::string text;
    for (char symbol : pretext) {
        if (!std::count(SYMBOLS.begin(), SYMBOLS.end(), symbol)) {
            text += symbol;
        }
    }
    for (auto& c : text) {
        c = std::toupper(c);
    }
    std::vector<std::vector<int>> text_ngrammas_numbers = text_into_numbers_ngrammas(text);
    std::vector<std::vector<int>> ciphertext_ngrammas_numbers;
    std::vector<int> ciphertext_ngramma;
    int letter = 0;
    size_t key_size = key_vec.size();
    for (const std::vector<int>& text_ngramma : text_ngrammas_numbers) {
        for (size_t i = 0; i < key_size; i++) {
            for (size_t j = 0; j < key_size; j++) {
                letter += key_vec[i][j] * text_ngramma[j];
            }
            ciphertext_ngramma.push_back(letter % ALPHABET_SIZE);
            letter = 0;
        }
        ciphertext_ngrammas_numbers.push_back(ciphertext_ngramma);
        ciphertext_ngramma.clear();
    }
    std::string ciphertext;
    for (const std::vector<int>& ngramma_numbers : ciphertext_ngrammas_numbers) {
        for (int number : ngramma_numbers) {
            ciphertext += static_cast<char>(ALPHABET[number]);
        }
    }
    return ciphertext;
}
