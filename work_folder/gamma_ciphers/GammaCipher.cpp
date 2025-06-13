#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "GammaCipher.h"

void GammaCipher::cipher()
        {
            auto gamma = get_gamma();
            const auto& text = get_text();
            const int x = get_param();
            for (int i{0}; i < text.size(); i++){
                int ind_gamma = gamma[i];
                int index_char = (text[i] + (ind_gamma * x)) % ALPHABET_SIZE;
                index_char = (index_char % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
                std::cout << gamma[i] << " " << text[i] << " " << x << " " << index_char << std::endl;
                ciphertext += ALPHABET[index_char];
                add_char_gamma(gamma, index_char);
            }
            return;
        }