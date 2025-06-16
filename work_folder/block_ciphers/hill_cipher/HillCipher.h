/**
 * \file
 * \brief Заголовочный файл класса HillCipher — реализация классического блочного шифра Хилла.
 */

#pragma once
#include "../../globals.h"
#include "../BlockCipher.h"
#include <string>
#include <vector>

/**
 * \class HillCipher
 * \brief Класс реализует классический шифр Хилла.
 */
class HillCipher : public BlockCipher
{
public:
    /**
     * \brief Конструктор, инициализирующий объект матрицей-ключом.
     * \param matrix Квадратная матрица-ключ.
     */
    HillCipher(std::vector<std::vector<int>> matrix) : BlockCipher(matrix) {}

    /**
     * \brief Выполняет шифрование или дешифрование текста методом Хилла.
     * \param pretext Входной текст.
     * \param option '1' — шифрование, '2' — дешифрование.
     * \return Результирующий текст.
     */
    std::string hill(std::string& pretext, char& option) override;
};
