/**
 * \file
 * \brief Заголовочный файл для класса AffineRecurrentCipher — рекуррентного аффинного шифра.
 */

#pragma once
#include <array>
#include <string>
#include <numeric>
#include "../SubstitutionCipher.h"
#include "globals.h"

/**
 * \class AffineRecurrentCipher
 * \brief Класс реализует аффинный шифр с рекуррентной сменой ключей на каждом шаге.
 *
 * Каждый блок текста шифруется новым ключом, полученным по рекуррентной формуле.
 */
class AffineRecurrentCipher {
protected:
    std::array<int, 2> key1; ///< Начальный ключ (a, b)
    std::array<int, 2> key2; ///< Второй ключ, использующийся в рекурсии

    /**
     * \brief Генерирует новый ключ на основе предыдущих двух по рекуррентному правилу.
     * \param key1 Первый ключ (a1, b1).
     * \param key2 Второй ключ (a2, b2).
     * \return Новый ключ (a3, b3) = (a1 * a2 mod N, b1 + b2 mod N).
     */
    std::array<int, 2> find_another_key(const std::array<int, 2>& key1, const std::array<int, 2>& key2);

public:
    /**
     * \brief Конструктор принимает два начальных ключа и валидирует их.
     * \param key1 Первый ключ (a1, b1).
     * \param key2 Второй ключ (a2, b2).
     */
    AffineRecurrentCipher(const std::array<int, 2>& key1, const std::array<int, 2>& key2)
        : key1(key1), key2(key2)
    {
        is_valid_key(key1);
        is_valid_key(key2);
    }

    /**
     * \brief Проверяет корректность ключа (a, b) для аффинного шифра.
     * \param key Ключ для проверки.
     * \return true, если ключ допустим; false и сообщение об ошибке в stderr — иначе.
     */
    bool is_valid_key(const std::array<int, 2>& key) {
        if (key[0] <= 0 || key[0] >= ALPHABET_SIZE) {
            std::cerr << "Alpha must be between 1 and " << ALPHABET_SIZE - 1 << "\n";
            return false;
        }
        if (std::gcd(key[0], ALPHABET_SIZE) != 1) {
            std::cerr << "Alpha must be coprime with " << ALPHABET_SIZE << "\n";
            return false;
        }
        if (key[1] < 0 || key[1] >= ALPHABET_SIZE) {
            std::cerr << "Beta must be between 0 and " << ALPHABET_SIZE - 1 << "\n";
            return false;
        }
        return true;
    }

    /**
     * \brief Основной метод шифрования и дешифрования.
     * \param text Входной текст.
     * \param choice '1' для шифрования, '2' для дешифрования.
     * \return Результат обработки текста.
     */
    std::string cipher(const std::string& text, const char choice);
};
