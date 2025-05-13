#include <iostream>
#include <string>
#include <cctype>
#include "VigenereCipher.h"
#include "..\..\globals.h"

std::vector<int> VigenereCipher::check_key() 
{
    while (true) {
        std::string key;
        std::cin >> key;
        if (is_alpha(key) and key.size() == len_key) {
            key = key;
            key_numbers = text_in_numbers(key);
        }
    }
}

void VigenereCipher::cipher()
{
    int x = -1 ? flag : 1;
    std::string ciphertext;
    for (int index: text_numbers){
        int ind_gamma = gamma[index];
        int index_char = (index + x * ind_gamma) % ALPHABET_SIZE;
        ciphertext += ALPHABET[index_char];
        add_char_gamma(index_char);
    }
}