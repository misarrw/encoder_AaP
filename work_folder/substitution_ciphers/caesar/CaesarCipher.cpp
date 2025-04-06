#include "CaesarCipher.hpp"
#include "../../globals.hpp"
#include <cctype>

std::string CaesarCipher::caesar_encryption(const std::string& text, const std::string& key) {
    std::string cipher_text;
    for (char letter : text) {
        if (letter == ' ') {
            cipher_text += ' ';
        } 
        else {
            size_t index = ALPHABET.find(toupper(letter));
            if (index != std::string::npos) {
                cipher_text += key[index];
            } 
            else {
                return "Oops, some symbols does not match any symbol from English alphabet :(";
            }
        }
    }
    return cipher_text;
}

std::string CaesarCipher::caesar_decryption(const std::string& cipher_text, const std::string& key)
{
    std::string decrypted_text;
    for (char letter: cipher_text) {
        if (letter == ' ') {
            decrypted_text += ' ';
        } 
        else {
            size_t index = key.find(toupper(letter));
            if (index != std::string::npos) {
                decrypted_text += ALPHABET[index];
            } 
            else {
                return "Oops, some symbols does not match any symbol from English alphabet :(";
            }
        }
    }
    return decrypted_text;
}