/**
 * \file
 * \brief Реализация вспомогательных методов класса SubFunction.
 */

#include <iostream>
#include "SubFunctions.h"
#include "globals.h"
#include "algorithm"

/**
 * \brief Преобразует строку в вектор чисел, соответствующих позициям букв в алфавите.
 * \param text Исходный текст, содержащий только буквы и пробелы.
 * \return Вектор числовых индексов символов или -1 для пробелов.
 */
std::vector<int> SubFunction::text_in_numbers(const std::string& text) {
    std::vector<int> result;

    for (char letter : text) {
        char upper_letter = std::toupper(static_cast<unsigned char>(letter));

        if (upper_letter == ' ') {
            result.push_back(-1);
            continue;
        }

        size_t letter_pos = ALPHABET.find(upper_letter);
        if (letter_pos != std::string::npos) {
            result.push_back(static_cast<int>(letter_pos));
            continue;
        }
    }

    return result;
}

/**
 * \brief Преобразует вектор чисел обратно в строку.
 * \param nums Вектор индексов символов.
 * \return Строка, соответствующая числовому представлению.
 */
std::string SubFunction::numbers_to_text(const std::vector<int>& nums) {
    std::string result;
    for (int num : nums) {
        if (num == -1) {
            result += ' ';
        } else {
            result += static_cast<char>('A' + num);
        }
    }
    return result;
}

/**
 * \brief Расширенный алгоритм Евклида для нахождения НОД и коэффициентов Безу.
 * \param a Первое число.
 * \param b Второе число.
 * \param x Результирующий коэффициент x такой, что ax + by = gcd(a, b).
 * \param y Результирующий коэффициент y такой, что ax + by = gcd(a, b).
 * \return НОД чисел a и b.
 */
int SubFunction::extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

/**
 * \brief Вычисляет обратное по модулю число.
 * \param a Число, для которого нужно найти обратное.
 * \param m Модуль.
 * \return Обратное число по модулю m, либо -1, если не существует.
 */
int SubFunction::modInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);

    if (gcd != 1) {
        return -1;
    } else {
        return (x % m + m) % m;
    }
}

/**
 * \brief Проверяет, состоит ли строка только из букв.
 * \param str Проверяемая строка.
 * \return true, если строка не пуста и содержит только буквы, иначе false.
 */
bool SubFunction::is_alpha(const std::string& str) {
    return !str.empty() &&
           std::all_of(str.begin(), str.end(),
               [](char c){ return isalpha(c); });
}
