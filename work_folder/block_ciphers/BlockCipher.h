#pragma once
#include <vector>


class BlockCipher
{
public:
    // Здесь должна быть функция проверки ключа, ЯРИК
    std::vector<std::vector<int>> text_into_numbers_ngrammas(std::string& text, std::vector<std::vector<int>>& key);
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