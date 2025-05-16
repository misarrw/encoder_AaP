#pragma once
#include <vector>
#include <string>

class VigenereCipher {
private:
    std::string key;

public:
    std::string vigenere(std::vector<int> gamma, std::vector<int> text_numbers, int operation);
};