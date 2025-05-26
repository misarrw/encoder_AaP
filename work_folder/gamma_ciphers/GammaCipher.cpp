#include <iostream>
#include <string>
#include <cctype>
#include "GammaCipher.h"
#include "globals.h"

void GammaCipher::cipher()
{
    std::string ciphertext;
    for (int index: text_numbers){
        int ind_gamma = gamma[index];
        int index_char = (index + x * ind_gamma) % ALPHABET_SIZE;
        ciphertext += ALPHABET[index_char];
        add_char_gamma(index_char);
    }
}