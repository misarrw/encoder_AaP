# include "../../../../globals.h"
# include <iostream>
# include <vector>
# include <string>
# include <cctype>
#include "VigenereOpenTextGamma.h"


void VigenereOpenTextGamma::creat_gamma()
{
    gamma.push_back(key_numbers[0]);
    for (int i{0}; i < (text_numbers.size() - 1); i++) {
        gamma.push_back(text_numbers[i]);
    }
}