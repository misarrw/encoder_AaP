#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <armadillo>
#include <numeric>
#include "..\globals.h"


class BlockCipher
{
protected:
    size_t key_size;
    std::vector<std::vector<int>> key_vec;
    arma::mat key;
    

public:
    BlockCipher(std::vector<std::vector<int>> matrix) : key_vec(matrix) 
    {
        key_size = key_vec.size();
        arma::mat key(key_size, key_size);
        for (size_t i = 0; i < key_vec.size(); ++i) {
            for (size_t j = 0; j < key_vec[i].size(); ++j) {
                key(i, j) = static_cast<double>(key_vec[i][j]);
            }
    }
        int determinant = static_cast<int>(round(arma::det(key))) % ALPHABET_SIZE;

        if (std::gcd(determinant, ALPHABET_SIZE) != 1) {
            throw std::runtime_error("\nRemember the GCD rules! The determinant of your matrix-key should have 1 as GCD with the number of the letters in your language.\nTry again:");
        }
    }
    // Здесь должна быть функция проверки ключа, ЯРИК
    std::vector<std::vector<int>> text_into_numbers_ngrammas(std::string& text);
    int extendedGCD(int a, int b, int& x, int& y);
    int modInverse(int a, int m);
    bool check_key(size_t block_size);
};


// struct MatrixKey : BlockCipher
// {
//     std::vector<std::vector<int>> data;
//     size_t size;

//     // Конструктор, принимающий двумерный вектор
//     MatrixKey(const std::vector<std::vector<int>>& matrix) 
//         : data(matrix), size(matrix.size()) 
//     {}

//     MatrixKey(size_t n) 
//         : data(n, std::vector<int>(n, 0)), size(n) 
//     {}

//     // Оператор доступа к элементам матрицы (неконстантная версия)
//     std::vector<int>& operator[](size_t index) {
//         return data[index];
//     }

//     // Получение размера матрицы
//     size_t getSize() const {
//         return size;
//     }
// };