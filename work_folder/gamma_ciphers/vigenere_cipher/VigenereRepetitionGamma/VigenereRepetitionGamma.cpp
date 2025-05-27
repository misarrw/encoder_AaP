#include "VigenereRepetitionGamma.h"
# include "..\..\..\globals.h"
# include <iostream>
# include <cctype>


void VigenereRepetitionGamma::creat_gamma()
{
    const size_t len_text = text_numbers.size();
    const size_t len_key = 100000000; 
    
    std::string gamma_str;
    gamma_str.reserve(len_text);
    

    for (size_t i{0}; i<len_text; ++i){
        gamma_str+=key[i%len_key]; //нужно в ключе сделать проверку, что длина не ноль
    }
    gamma = text_in_numbers(gamma_str);
}

