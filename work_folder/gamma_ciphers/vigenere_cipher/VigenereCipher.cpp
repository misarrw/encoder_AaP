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
