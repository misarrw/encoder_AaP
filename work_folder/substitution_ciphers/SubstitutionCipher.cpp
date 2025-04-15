#include <iostream>
#include "SubstitutionCipher.h"
#include "../globals.hpp"


int SubstitutionCipher::opposite_alpha(int alpha)
{
    int counter = 1;
    int remainder = ((counter * ALPHABET_SIZE) + 1) % alpha;
    while (remainder != 0) {
        counter++;
        remainder = (counter * ALPHABET_SIZE + 1) % alpha;
    }
    int o_alpha = (counter * ALPHABET_SIZE + 1) / alpha;
    return o_alpha;
}