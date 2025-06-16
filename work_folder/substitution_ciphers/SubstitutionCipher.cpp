/**
 * \file
 * \brief Реализация метода класса SubstitutionCipher для получения обратного значения по модулю.
 */

#include <iostream>
#include "SubstitutionCipher.h"
#include "globals.h"
#include "numeric"

/**
 * \brief Вычисляет значение, обратное alpha по модулю ALPHABET_SIZE.
 * \param alpha Значение, для которого ищется обратное по модулю ALPHABET_SIZE.
 * \return Число o_alpha, такое что (alpha * o_alpha) % ALPHABET_SIZE == 1.
 */
int SubstitutionCipher::opposite_alpha(int& alpha)
{
    int counter = 1;
    int remainder = ((counter * ALPHABET_SIZE) + 1) % alpha;
    while (remainder != 0) {
        counter++;
        remainder = (counter * ALPHABET_SIZE + 1) % alpha;
    }
    int o_alpha = (counter * ALPHABET_SIZE + 1) / alpha;
    return o_alpha;
}
