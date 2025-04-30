#include <iostream>
#include <AffineCipher.h>
#include <..\..\globals.h>
#include <cctype>


AffineCipher::AffineCipher(const std::array<int, 2>& key, const std::string& t, bool f)
{
    text = t;
    alpha = key[0];
    beta = key[1];
    flag = f;
}


std::string AffineCipher::affine()
{
    std::string cipher_text;
    if (flag) {
        AffineCipher coder = AffineCoder();
    } else {
        AffineCipher coder = AffineEncoder();
        alpha = opposite_alpha(alpha);
    }
    for (char c : text) {
        c = toupper(c);
        int index = ALPHABET.find(c);
        if (index == std::string::npos){
            cipher_text += c;
            continue;
        }
        int enc_c = cipher(index);
        cipher_text += ALPHABET[enc_c];
    }
    
    return cipher_text;
}

int AffineCoder::cipher(int &index)
{
    return (alpha * index + beta) % ALPHABET_SIZE;
}

int AffineEncoder::cipher(int &index)
{
    return (alpha * (index - beta + ALPHABET_SIZE)) % ALPHABET_SIZE;
}
