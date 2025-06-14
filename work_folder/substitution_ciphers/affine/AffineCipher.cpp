#include <iostream>
#include "AffineCipher.h"
#include "../../globals.h"
#include <cctype>


AffineCipher::AffineCipher(const std::string& text):text(text) {}


std::string AffineCipher::affine(Affine& coder)
{
    std::string cipher_text;
    std::cout << text;
    for (char c : text) {
        c = toupper(c);
        int index = ALPHABET.find(c);
        if (index == std::string::npos){
            cipher_text += c;
            continue;
        }
        int enc_c = coder.cipher(index);
        cipher_text += ALPHABET[enc_c];
    }
    return cipher_text;
}

int AffineCoder::cipher(int &index)
{
    std::cout << "2";
    return (alpha * index + beta) % ALPHABET_SIZE;
}

int AffineEncoder::cipher(int &index)
{
    return (alpha * (index - beta + ALPHABET_SIZE)) % ALPHABET_SIZE;
}
