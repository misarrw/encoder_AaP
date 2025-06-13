#include "HillRecurrentCipher.h"
#include <string>
#include <vector>
#include "../BlockCipher.h"
#include "globals.h"
#include <cctype>
#include <algorithm>
#include <armadillo>

std::vector<std::vector<int>> HillRecurrentCipher::generate_next_key(std::vector<std::vector<int>> key1, std::vector<std::vector<int>> key2) {
    arma::mat arma_key1 = make_arma_matrix(key1);
    arma::mat arma_key2 = make_arma_matrix(key2);

    arma::mat arma_new_key = arma_key1 * arma_key2;

    std::vector<std::vector<int>> new_key(
        arma_new_key.n_rows,
        std::vector<int>(arma_new_key.n_cols)
    );

    for (size_t i = 0; i < arma_new_key.n_rows; ++i) {
        for (size_t j = 0; j < arma_new_key.n_cols; ++j) {
            new_key[i][j] = std::fmod(arma_new_key(i,j), 26.0);
            if (new_key[i][j] < 0) {
                new_key[i][j] += 26.0; 
            }
        }
    }
    
    return new_key;
}



std::string HillRecurrentCipher::hill(std::string& pretext, int& option) {
    std::vector<std::vector<int>> current_key = key1;
    std::vector<std::vector<int>> next_key = key2;
    
    if (option == 2) { 
        current_key = find_inverse_matrix(key1);
        next_key = find_inverse_matrix(key2);
    }


    std::string text;
    for (char symbol : pretext) {
        if (std::isalpha(symbol)) {
            text += std::toupper(symbol);
        }
    }

    std::vector<std::vector<int>> text_ngrammas_numbers = text_into_numbers_ngrammas(text);
    std::vector<std::vector<int>> ciphertext_ngrammas_numbers;
    std::vector<int> ciphertext_ngramma;
    
    for (std::vector<int> text_ngramma: text_ngrammas_numbers) {
        for (size_t i = 0; i < current_key.size(); i++) {
            int letter = 0;
            for (size_t j = 0; j < current_key.size(); j++) {
                letter += static_cast<int>(std::round(current_key[i][j])) * text_ngramma[j];
            }
            letter = letter % ALPHABET_SIZE;
            ciphertext_ngramma.push_back(letter);
        }
        ciphertext_ngrammas_numbers.push_back(ciphertext_ngramma);
        ciphertext_ngramma.clear();
    
    if (option == 1) {
        std::vector<std::vector<int>> new_key = generate_next_key(current_key, next_key);
        current_key = next_key;
        next_key = new_key; }
    if (option == 2) {
        std::vector<std::vector<int>> new_key = generate_next_key(next_key, current_key);
        current_key = next_key;
        next_key = new_key; }
    
    }
    
    std::string ciphertext;
    for (std::vector<int> ngramma_numbers: ciphertext_ngrammas_numbers) {
        for (int number: ngramma_numbers) {
            ciphertext += static_cast<char>(ALPHABET[number]);
        }
    }
    return ciphertext;
}

