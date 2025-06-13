#include "CaesarCipher.h"
#include "globals.h"
#include <cctype>

std::string CaesarCipher::caesar_encryption(const std::string& text) {
    std::string ciphertext;
    for (char letter : text) {
        if (!isalpha(letter)) {
            ciphertext += letter;
        } 
        else {
            size_t index = ALPHABET.find(toupper(letter));
            if (index != std::string::npos) {
                ciphertext += key[index];
            } 
            else {
                return "Oops, some symbols do not match any symbol from English alphabet :(";
            }
        }
    }
    for (auto& c : ciphertext) {
        c = std::toupper(c);
    }
    return ciphertext;
}

std::string CaesarCipher::caesar_decryption(const std::string& ciphertext)
{
    std::string decrypted_text;
    for (auto& c : key) {
        c = std::toupper(c);
    }
    for (char letter: ciphertext) {
        if (!isalpha(letter)) {
            decrypted_text += letter;
        } 
        else {
            size_t index = key.find(toupper(letter));
            if (index != std::string::npos) {
                decrypted_text += ALPHABET[index];
            } 
            else {
                return "Oops, some symbols do not match any symbol from English alphabet :(";
            }
        }
    }
    for (auto& c : decrypted_text) {
        c = std::toupper(c);
    }
    return decrypted_text;
}


void CaesarCipher::check_caesar_key(std::unordered_set<char> key_set)
{
    if (key_set.size() != ALPHABET_SIZE) {
        throw InvalidInputError("\nYour key is too short or incorrect. Check the tip and try again");
    }
}