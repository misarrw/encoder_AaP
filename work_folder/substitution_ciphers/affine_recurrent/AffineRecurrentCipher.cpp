/**
 * \file
 * \brief Реализация методов класса AffineRecurrentCipher — рекуррентного аффинного шифра.
 */

#include <iostream>
#include <array>
#include <string>
#include <numeric>
#include "../../globals.h"
#include "AffineRecurrentCipher.h"
#include "../../../work_folder/SubFunctions.h"
#include "../../../work_folder/substitution_ciphers/SubstitutionCipher.h"

/**
 * \brief Вычисляет следующий ключ по рекуррентной формуле.
 * \param key1 Первый ключ в виде массива из двух целых чисел.
 * \param key2 Второй ключ.
 * \return Новый ключ, полученный по рекуррентному правилу.
 */
std::array<int, 2> AffineRecurrentCipher::find_another_key(const std::array<int, 2>& key1,
                                                           const std::array<int, 2>& key2)
{
    return {
        (key1[0] * key2[0]) % ALPHABET_SIZE,
        (key1[1] + key2[1]) % ALPHABET_SIZE
    };
}

/**
 * \brief Выполняет шифрование или дешифрование текста с помощью рекуррентного аффинного шифра.
 * \param text Входной текст (может содержать пробелы).
 * \param choice '1' — шифрование, '2' — дешифрование.
 * \return Результирующий зашифрованный или расшифрованный текст.
 * \throws std::invalid_argument Если передано недопустимое значение choice или встречены недопустимые символы.
 */
std::string AffineRecurrentCipher::cipher(const std::string& text,
                                          const char choice)
{
    if (text.empty()) return "";

    std::vector<int> pre_result;
    std::array<int, 2> current_key, next_key;

    if (choice == '1') {
        current_key = key1;
        next_key = key2;
    }
    else if (choice == '2') {
        int tmp_a1 = key1[0];
        int tmp_a2 = key2[0];
        current_key = {
            SubstitutionCipher::opposite_alpha(tmp_a1),
            key1[1]
        };
        next_key = {
            SubstitutionCipher::opposite_alpha(tmp_a2),
            key2[1]
        };
    }
    else {
        throw std::invalid_argument("Invalid choice value. Use 1 for encryption or 2 for decryption");
    }

    for (char c : text) {
        char upper = std::toupper(static_cast<unsigned char>(c));
        int num;
        if (upper == ' ') {
            pre_result.push_back(-1);
            continue;
        }
        if (SYMBOLS.find(upper) != std::string::npos) {
            pre_result.push_back(static_cast<int>(upper));
            continue;
        }
        size_t pos = ALPHABET.find(upper);
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid character: " + std::string(1, c));
        }
        num = static_cast<int>(pos);

        int modified;
        if (choice == '1') {
            modified = (current_key[0] * num + current_key[1]) % ALPHABET_SIZE;
        }
        else {
            modified = (current_key[0] * (num - current_key[1])) % ALPHABET_SIZE;
        }

        if (modified < 0) modified += ALPHABET_SIZE;
        pre_result.push_back(modified);

        auto new_key = find_another_key(current_key, next_key);
        current_key = next_key;
        next_key = new_key;
    }

    std::string result = SubFunction::numbers_to_text(pre_result);
    return result;
}
