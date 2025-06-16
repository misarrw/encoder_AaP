/**
 * \file
 * \brief Реализация метода VigenereCipher::check_key — проверка и ввод ключа.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "VigenereCipher.h"
#include "../../globals.h"

/**
 * \brief Выполняет ввод и проверку ключа для шифра Виженера.
 */
void VigenereCipher::check_key()
{
    while (true) {
        std::string key_input;
        std::cout << "Enter the key: " << std::endl;
        std::cin >> key_input;

        if (is_alpha(key_input) && key_input.size() <= get_len_key()) {
            key = key_input;
            key_numbers = text_in_numbers(key);
            return;
        }

        std::cout << "Key input error" << std::endl;
    }
}

