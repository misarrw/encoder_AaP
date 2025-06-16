/**
 * \file
 * \brief Реализация методов класса VigenereCipherTextGamma — гамма из текста шифра.
 */

#include "VigenereCipherTextGamma.h"

/**
 * \brief Инициализирует гамму первым символом ключа.
 */
void VigenereCipherTextGamma::create_gamma()
{
    gamma.push_back(key_numbers[0]);
}

/**
 * \brief Добавляет очередной шифрованный символ в гамму.
 * \param gamma_cipher Текущая гамма.
 * \param i Индекс символа, который будет добавлен в гамму.
 */
void VigenereCipherTextGamma::add_char_gamma(std::vector<int>& gamma_cipher, int i) 
{
    gamma_cipher.push_back(i);
}
