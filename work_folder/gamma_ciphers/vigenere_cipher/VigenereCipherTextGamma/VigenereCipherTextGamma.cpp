#include "VigenereCipherTextGamma.h"

void VigenereCipherTextGamma::creat_gamma()
{
    gamma.push_back(key_numbers[0]);
}

void VigenereCipherTextGamma::add_char_gamma(std::vector<int>& gamma_cipher, int i)
{
    gamma_cipher.push_back(i);
}