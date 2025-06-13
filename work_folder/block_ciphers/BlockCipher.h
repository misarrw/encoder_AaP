#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <armadillo>
#include <numeric>
#include "..\globals.h"
#include "..\SubFunctions.h"

class BlockCipher : public SubFunction
{
protected:
    std::vector<std::vector<int>> key_vec;
    void check_hill_key(std::vector<std::vector<int>> matrix, int determinant);
    

public:
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
    std::vector<std::vector<int>> text_into_numbers_ngrammas(std::string& text);
    bool check_key(size_t key_space, size_t block_size);
    virtual std::string hill(std::string& pretext, char& option) {
        throw std::runtime_error("Method 'hill' not implemented in base class.");
    }

    arma::mat make_arma_matrix(std::vector<std::vector<int>>& key_vec);

    std::vector<std::vector<int>> find_inverse_matrix();

    virtual ~BlockCipher() = default;
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