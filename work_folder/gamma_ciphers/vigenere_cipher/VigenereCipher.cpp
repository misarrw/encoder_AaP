#include "VigenereCipher.h"
#include <iostream>
#include "..\..\globals.h"


std::string VigenereCipher::vigenere(std::vector<int> gamma, std::vector<int> text_numbers, int operation)
{
    std::vector<int> ciphertext_or_text_numbers;
    size_t text_numbers_size = text_numbers.size();
    for (int i = 0; i < text_numbers_size;++i) {
        if (operation == 1) {
            ciphertext_or_text_numbers.push_back((gamma[i] + text_numbers[i]) % ALPHABET_SIZE);
        }
        else {
            ciphertext_or_text_numbers.push_back((text_numbers[i] - gamma[i]) % ALPHABET_SIZE);
        }
    }
    std::string ciphertext_or_text;
    for (int number: ciphertext_or_text_numbers) {
        ciphertext_or_text += static_cast<char>(ALPHABET[number]);
    }
    for (auto& c : ciphertext_or_text) {
        c = std::toupper(c);
    }
    return ciphertext_or_text;
}