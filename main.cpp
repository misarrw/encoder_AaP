#include <iostream>
#include "work_folder/substitution_ciphers/caesar/CaesarCipher.hpp"
#include <cctype>

int main()
{
    CaesarCipher cipher;
    std::string text = "HELLO WORLD";
    std::string key = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

    std::cout << cipher.caesar_encryption(text, key) << std::endl;

    std::string cipher_text = "SVOOL DLIOW";
    std::cout << cipher.caesar_decryption(cipher_text, key) << std::endl;

    return 0;
}