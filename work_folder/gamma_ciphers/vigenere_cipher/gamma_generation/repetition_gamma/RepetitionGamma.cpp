# include "RepetitionGamma.hpp"
# include "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/work_folder/SubFunctions.hpp"
# include "globals.hpp"
# include <iostream>
# include <cctype>


std::vector<int> VigenereCipher :: RepetitionGamma :: repgamma(const std::string& key, std::vector<int>& text_numbers)
{
    const size_t len_text = text_numbers.size();
    const size_t len_key = key.size(); 
    
    std::string gamma_str;
    gamma_str.reserve(len_text);

    for (size_t i{0}; i<len_text; ++i){
        gamma_str+=key[i%len_key]; //нужно в ключе сделать проверку, что длина не ноль
    }
    std::vector<int> gamma = SubFunction::text_in_numbers(gamma_str);
    return gamma;
}

