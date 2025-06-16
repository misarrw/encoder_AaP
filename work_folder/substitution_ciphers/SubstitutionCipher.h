/**
 * \file
 * \brief Заголовочный файл для SubstitutionCipher — класса с базовой логикой подстановочного шифрования.
 */

#pragma once
#include "../SubFunctions.h"

/**
 * \class SubstitutionCipher
 * \brief Базовый класс для подстановочных шифров. Наследует вспомогательные функции от SubFunction.
 */
class SubstitutionCipher : public SubFunction
{
public:
    /**
     * \brief Возвращает число, противоположное данному по модулю размера алфавита.
     * \param alpha Значение, для которого вычисляется противоположное по модулю ALPHABET_SIZE.
     * \return Число в диапазоне [0, ALPHABET_SIZE), которое является модульным отрицанием alpha.
     */
    static int opposite_alpha(int& alpha);
};
