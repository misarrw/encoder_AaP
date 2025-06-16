/**
 * \file
 * \brief Заголовочный файл класса CaesarCipher — реализация классического шифра Цезаря.
 */

#pragma once
#include <string>
#include "../SubstitutionCipher.h"
#include <unordered_set>
#include "../../globals.h"

/**
 * \class CaesarCipher
 * \brief Класс реализует шифрование и дешифрование методом Цезаря.
 */
class CaesarCipher : public SubstitutionCipher {
private:
    std::string key; ///< Ключ шифрования (перестановка алфавита)

    /**
     * \brief Проверяет корректность ключа: все символы алфавита должны быть уникальны и присутствовать.
     * \param key_set Множество символов, составляющих ключ.
     * \throws InvalidInputError Если количество символов не совпадает с ALPHABET_SIZE.
     */
    void check_caesar_key(std::unordered_set<char> key_set);

public:
    /**
     * \brief Конструктор принимает строку-ключ и выполняет его проверку.
     * \param k Ключ шифрования — строка-перестановка букв алфавита.
     */
    CaesarCipher(std::string k) : key(k) 
    {
        std::unordered_set<char> key_set;
        for (char symbol : key) {
            key_set.insert(symbol);
        }
        try {
            check_caesar_key(key_set);
        }
        catch (const InvalidInputError& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    /**
     * \brief Шифрует текст методом Цезаря.
     * \param text Исходный открытый текст.
     * \return Зашифрованный текст.
     */
    std::string caesar_encryption(const std::string& text);

    /**
     * \brief Расшифровывает текст, зашифрованный методом Цезаря.
     * \param cipher_text Зашифрованный текст.
     * \return Расшифрованный открытый текст.
     */
    std::string caesar_decryption(const std::string& cipher_text);
};
