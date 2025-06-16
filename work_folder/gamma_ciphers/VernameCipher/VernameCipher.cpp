/**
 * \file
 * \brief Реализация метода создания гаммы в шифре Вернама.
 */

#include "VernameCipher.h"
#include <iostream>
#include <vector>
#include <random>
#include "globals.h"

/**
 * \brief Генерирует случайную гамму для шифрования методом Вернама.
 */
void VernameCipher::create_gamma() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, ALPHABET_SIZE - 1);

    gamma.reserve(len_text);

    for (size_t i = 0; i < len_text; ++i) {
        gamma.push_back(dist(gen));
    }

    ciphertext += "Key: " + numbers_to_text(gamma) + " ";
}
