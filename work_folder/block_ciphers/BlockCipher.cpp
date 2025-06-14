#include "BlockCipher.h"
#include "globals.h"
#include <string>


std::vector<std::vector<int>> BlockCipher::text_into_numbers_ngrammas(std::string& text)
{
    std::vector<std::string> ngrammas_list;
    size_t key_size = key_vec.size();
    size_t text_size = text.size();

    while (text.size() % key_size != 0) {
        text += 'X';
    }

    for (size_t i = 0; i < text.size(); i += key_size) {
        ngrammas_list.push_back(text.substr(i, key_size));
    }
    std::vector<int> ngramma_numbers;
    std::vector<std::vector<int>> ngrammas_numbers;
    for (std::string ngramma: ngrammas_list) {
        for (char letter: ngramma) {
            ngramma_numbers.push_back(ALPHABET.find(letter));
        }
        ngrammas_numbers.push_back(ngramma_numbers);
        ngramma_numbers.clear();
    }
    return ngrammas_numbers;
}


arma::mat BlockCipher::make_arma_matrix(std::vector<std::vector<int>>& key_vec) 
{
    arma::mat key(key_vec.size(), key_vec[0].size());
    for (size_t i = 0; i < key_vec.size(); ++i) {
        for (size_t j = 0; j < key_vec[i].size(); ++j) {
            key(i, j) = static_cast<double>(key_vec[i][j]);
        }
    }
    return key;
}


std::vector<std::vector<int>> BlockCipher::find_inverse_matrix(std::vector<std::vector<int>> key_vec) {
    arma::mat arma_matrix = make_arma_matrix(key_vec);

    double det = arma::det(arma_matrix);
    int determinant = static_cast<int>(round(det)) % ALPHABET_SIZE;
    determinant = (determinant % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;

    int opposite_determinant = modInverse(determinant, ALPHABET_SIZE);
    if (opposite_determinant == -1) {
        throw std::runtime_error("Matrix is not invertible modulo ALPHABET_SIZE");
    }

    arma::mat adj_matrix = det * arma::inv(arma_matrix);

    std::vector<std::vector<int>> inverse_matrix(adj_matrix.n_rows, std::vector<int>(adj_matrix.n_cols));
    for (size_t i = 0; i < adj_matrix.n_rows; ++i) {
        for (size_t j = 0; j < adj_matrix.n_cols; ++j) {
            int value = static_cast<int>(round(adj_matrix(i, j)));
            inverse_matrix[i][j] = (value * opposite_determinant) % ALPHABET_SIZE;
            if (inverse_matrix[i][j] < 0) {
                inverse_matrix[i][j] += ALPHABET_SIZE;
            }
        }
    }

    return inverse_matrix;
}


void BlockCipher::check_hill_key(std::vector<std::vector<int>> matrix, int determinant)
{
    if (matrix.size() != matrix[0].size()) {
        throw InvalidInputError("\nYour matrix is not square :(");
    }
    if (std::gcd(determinant, ALPHABET_SIZE) != 1) {
        throw InvalidInputError("\nRemember the GCD rules! The determinant of your matrix-key should have 1 as GCD with the number of the letters in your language.\nTry again:");
    }
}