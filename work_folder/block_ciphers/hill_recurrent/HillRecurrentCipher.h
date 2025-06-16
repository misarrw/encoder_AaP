/**
 * \file
 * \brief Заголовочный файл для HillRecurrentCipher — рекуррентный вариант шифра Хилла.
 */

#pragma once
#include "../../globals.h"
#include "../BlockCipher.h"
#include <string>
#include <vector>

/**
 * \class HillRecurrentCipher
 * \brief Расширение шифра Хилла, в котором каждый блок шифруется с использованием динамически изменяемого ключа.
 *
 * Ключи изменяются на каждой итерации по рекуррентному правилу (умножение матриц).
 */
class HillRecurrentCipher : public BlockCipher {
protected:
    std::vector<std::vector<int>> key1; ///< Начальный ключ 1
    std::vector<std::vector<int>> key2; ///< Начальный ключ 2

public:
    /**
     * \brief Конструктор, принимающий два начальных ключа.
     * \param key1 Первый ключ (матрица).
     * \param key2 Второй ключ (матрица).
     */
    HillRecurrentCipher(const std::vector<std::vector<int>>& key1, const std::vector<std::vector<int>>& key2)
        : BlockCipher(key1), key1(key1), key2(key2) {}

    /**
     * \brief Генерирует следующий ключ по рекуррентному правилу.
     * \param key1 Первый ключ (текущий).
     * \param key2 Второй ключ (предыдущий).
     * \return Новый ключ — результат умножения key1 на key2 по модулю 26.
     */
    std::vector<std::vector<int>> generate_next_key(std::vector<std::vector<int>> key1, std::vector<std::vector<int>> key2);

    /**
     * \brief Выполняет шифрование или дешифрование текста по методу Хилла с рекуррентным обновлением ключей.
     * \param pretext Входной текст.
     * \param option '1' — шифрование, '2' — дешифрование.
     * \return Результирующий текст.
     */
    std::string hill(std::string& pretext, char& option) override;
};
