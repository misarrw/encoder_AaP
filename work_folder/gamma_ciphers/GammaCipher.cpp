/**
 * \file
 * \brief Реализация метода GammaCipher::cipher — основного процесса гаммирования текста.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "GammaCipher.h"

/**
 * \brief Выполняет шифрование или дешифрование текста с использованием гаммы.
 */
void GammaCipher::cipher() 
{
    auto gamma = get_gamma();             
    const auto& text = get_text();       
    const int x = get_param();            
    for (int i = 0; i < text.size(); i++) {
        int ind_gamma = gamma[i];          
        char c = toupper(text[i]);         
        int index = ALPHABET.find(c);      
        if (index == std::string::npos) {
            ciphertext += c;
            add_char_gamma(gamma, gamma.back());
            continue;
        }
        int index_char = (index + (ind_gamma * x)) % ALPHABET_SIZE;
        index_char = (index_char % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
        ciphertext += ALPHABET[index_char];
        add_char_gamma(gamma, index_char);
    }
    return;
}
