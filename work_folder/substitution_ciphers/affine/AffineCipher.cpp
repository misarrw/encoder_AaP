/**
 * \file
 * \brief Реализация класса AffineCipher: методы шифрования и утилиты для преобразования текста.
 */

#include <iostream>
#include "AffineCipher.h"
#include "../../globals.h"
#include <cctype>

/**
 * \brief Конструктор, сохраняющий переданный текст.
 * \param text Входной текст, который будет шифроваться или дешифровываться.
 */
AffineCipher::AffineCipher(const std::string& text):text(text) {}

/**
 * \brief Выполняет аффинное шифрование или дешифрование текста.
 * \param coder Структура с параметрами alpha и beta.
 * \return Зашифрованный или расшифрованный текст.
 */
std::string AffineCipher::affine(Affine& coder)
{
    std::string cipher_text;
    for (char c : text) {
        c = toupper(c);
        int index = ALPHABET.find(c);
        if (index == std::string::npos){
            cipher_text += c;
            continue;
        }
        int enc_c = coder.cipher(index);
        cipher_text += ALPHABET[enc_c];
    }
    return cipher_text;
}
/**
 * \brief Шифрование
 * \return Индекс зашифровоного символа
 */
int AffineCoder::cipher(int &index)
{
    return (alpha * index + beta) % ALPHABET_SIZE;
}

/**
 * \brief Расшифрование
 * \return Индекс расшифровоного символа
 */
int AffineEncoder::cipher(int &index)
{
    return (alpha * (index - beta + ALPHABET_SIZE)) % ALPHABET_SIZE;
}
