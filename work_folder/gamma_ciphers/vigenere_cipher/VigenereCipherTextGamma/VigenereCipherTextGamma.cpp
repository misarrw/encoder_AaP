#include "VigenereCipherTextGamma.h"

void VigenereCipherTextGamma::creat_gamma()
{
    gamma.push_back(key_numbers[0]);
}

void VigenereCipherTextGamma::add_char_gamma(int i)
{
    gamma.push_back(i);
}