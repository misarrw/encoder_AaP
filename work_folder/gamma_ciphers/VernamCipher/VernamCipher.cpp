#include "VernamCipher.h"
#include <iostream>
#include <vector>
#include <random>  
#include "globals.h"

void VernamCipher::creat_gamma() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, ALPHABET_SIZE); 

    gamma.reserve(len_text);

    for (size_t i = 0; i < len_text; ++i) {
        gamma.push_back(dist(gen)); 
    }
}
