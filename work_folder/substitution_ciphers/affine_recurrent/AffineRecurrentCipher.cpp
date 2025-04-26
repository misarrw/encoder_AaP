#include <iostream>
#include <array>
#include <string>
#include "AffineRecurrentCipher.hpp"
#include "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/work_folder/SubFunctions.hpp"
#include "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/work_folder/substitution_ciphers/SubstitutionCipher.hpp"
#include "globals.hpp"
#include <numeric>


std::vector<std::array<int, 2>> AffineRecurrentCipher::all_keys(
    const std::array<int, 2>& key1,
    const std::array<int, 2>& key2,
    const std::string& text) 
{
    std::vector<std::array<int, 2>> keys;
    keys.push_back(key1);
    keys.push_back(key2);

    for (size_t i = 2; i < text.size(); ++i) {
        int new_a = (keys[i-1][0] * keys[i-2][0]) % ALPHABET_SIZE;
        int new_b = (keys[i-1][1] + keys[i-2][1]) % ALPHABET_SIZE;
        keys.push_back({new_a, new_b});
    }
    
    return keys;
}

std::string AffineRecurrentCipher::encryption(const std::string& text, 
                                            const std::array<int, 2>& key1,
                                            const std::array<int, 2>& key2) 
{
    if (text.empty()) return "";

    auto keys = all_keys(key1, key2, text);
    std::vector<int> pre_result;
    size_t key_index = 0;
    std::vector<int> text_in_nums = SubFunction::text_in_numbers(text);
    
    for (int c : text_in_nums) {
        const auto& key = keys[key_index++];
        if (c == -1) { pre_result.push_back(c);} 
        else {
            int encrypted = (key[0] * c + key[1]) % ALPHABET_SIZE;
            if (encrypted < 0) encrypted += ALPHABET_SIZE;
            pre_result.push_back(encrypted);
            }
    }
    std::string result = SubFunction::numbers_to_text(pre_result);
    
    return result;
}

std::vector<std::array<int, 2>> AffineRecurrentCipher::decryption_keys(const std::array<int, 2>& key1, const std::array<int, 2>& key2, const std::string& text) 
{
    std::vector<std::array<int, 2>> dec_keys;
    
    int a1 = key1[0];
    int b1 = key1[1];
    int a2 = key2[0];  
    int b2 = key2[1];
    
    int a1_inv = SubstitutionCipher::opposite_alpha(a1);
    int a2_inv = SubstitutionCipher::opposite_alpha(a2);

    dec_keys.push_back({a1_inv, b1});
    dec_keys.push_back({a2_inv, b2});

    for (size_t i = 2; i < text.size(); i++) {  
        int new_a = (dec_keys[i-2][0] * dec_keys[i-1][0]) % ALPHABET_SIZE;  
        int new_b = (dec_keys[i-2][1] + dec_keys[i-1][1]) % ALPHABET_SIZE;  
        dec_keys.push_back({new_a, new_b}); 
    }
    
    return dec_keys;
}


std::string AffineRecurrentCipher::decryption(const std::string& ciphertext, const std::array<int, 2>& key1, const std::array<int, 2>& key2) 
{
    if (ciphertext.empty()) return "";

    auto dec_keys = decryption_keys(key1, key2, ciphertext);
    std::vector<int> pre_result;
    size_t key_index = 0;
    std::vector<int> text_in_nums = SubFunction::text_in_numbers(ciphertext);
    
    for (int c : text_in_nums) {
        const auto& key = dec_keys[key_index++];
        if (c == -1) { pre_result.push_back(c);}
        else {
            int decrypted = (key[0] * (c - key[1])) % ALPHABET_SIZE;
            if (decrypted < 0) decrypted += ALPHABET_SIZE;
            pre_result.push_back(decrypted);
        }
        
    }
    std::string result = SubFunction::numbers_to_text(pre_result);
    return result;
}