/**
 * \file
 * \brief Заголовочный файл абстрактного базового класса BlockCipher для блочных шифров.
 */

#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <armadillo>
#include <numeric>
#include "../globals.h"
#include "../SubFunctions.h"

/**
 * \class BlockCipher
 * \brief Абстрактный базовый класс для всех блочных шифров.
 */
class BlockCipher : public SubFunction
{
protected:
    std::vector<std::vector<int>> key_vec; ///< Матрица-ключ в виде двумерного вектора

    /**
     * \brief Проверяет, пригодна ли матрица-ключ для использования в шифре Хилла.
     * \param matrix Ключевая матрица.
     * \param determinant Определитель ключевой матрицы.
     * \throws InvalidInputError Если матрица не является допустимой.
     */
    void check_hill_key(std::vector<std::vector<int>> matrix, int determinant);

    /**
     * \brief Вычисляет обратную матрицу методом Гаусса-Жордана.
     * \param mat Входная матрица.
     * \return Обратная матрица в формате arma::mat.
     */
    arma::mat gauss_jordan_inverse_arma(const arma::mat& mat);

public:
    /**
     * \brief Конструктор инициализирует матрицу-ключ и проверяет её корректность.
     * \param matrix Матрица-ключ.
     */
    BlockCipher(std::vector<std::vector<int>> matrix) : key_vec(matrix) 
    {
        arma::mat key(key_vec.size(), key_vec[0].size());
        for (size_t i = 0; i < key_vec.size(); ++i) {
            for (size_t j = 0; j < key_vec[i].size(); ++j) {
                key(i, j) = static_cast<double>(key_vec[i][j]);
            }
        }

        int determinant = static_cast<int>(round(arma::det(key))) % ALPHABET_SIZE;

        try {
            check_hill_key(matrix, determinant);
        }
        catch (const InvalidInputError& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    /**
     * \brief Разбивает текст на n-граммы и преобразует их в числовую матрицу.
     * \param text Входной текст.
     * \return Вектор n-грамм, представленных как векторы чисел.
     */
    std::vector<std::vector<int>> text_into_numbers_ngrammas(std::string& text);

    /**
     * \brief Проверяет корректность ключа по размеру блока и полному размеру пространства.
     * \param key_space Количество элементов в ключе.
     * \param block_size Ожидаемый размер блока (n).
     * \return true, если размеры допустимы.
     */
    bool check_key(size_t key_space, size_t block_size);

    /**
     * \brief Преобразует двумерный вектор в arma::mat.
     * \param key_vec Матрица-ключ.
     * \return arma::mat, соответствующая входному вектору.
     */
    arma::mat make_arma_matrix(std::vector<std::vector<int>>& key_vec);

    /**
     * \brief Находит обратную матрицу по модулю ALPHABET_SIZE.
     * \param key_vec Матрица-ключ.
     * \return Обратная матрица.
     */
    std::vector<std::vector<int>> find_inverse_matrix(std::vector<std::vector<int>> key_vec);

    /**
     * \brief Виртуальный метод hill — должен быть переопределён в подклассе.
     * \param pretext Текст для шифрования/дешифрования.
     * \param option Флаг режима ('e'/'d').
     * \return Результат шифрования.
     * \throws std::runtime_error Если метод не переопределён в дочернем классе.
     */
    virtual std::string hill(std::string& pretext, char& option) {
        throw std::runtime_error("Method 'hill' not implemented in base class.");
    }

    /**
     * \brief Виртуальный деструктор.
     */
    virtual ~BlockCipher() = default;
};
