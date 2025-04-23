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
    
    // Проверяем только первые два ключа
    if (std::gcd(key1[0], ALPHABET_SIZE) != 1) {
        throw std::invalid_argument("First key's 'a' must be coprime with ALPHABET_SIZE");
    }
    if (std::gcd(key2[0], ALPHABET_SIZE) != 1) {
        throw std::invalid_argument("Second key's 'a' must be coprime with ALPHABET_SIZE");
    }

    // Считаем только буквы (игнорируем пробелы)
    size_t letter_count = std::count_if(text.begin(), text.end(), 
        [](char c) { return c != ' '; });
    
    // Генерируем ключи для всех букв (без проверки взаимной простоты)
    for (size_t i = 2; i < letter_count; ++i) {
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
    std::string result;
    size_t key_index = 0;
    
    for (char c : text) {
        if (c == ' ') {
            result += ' ';
            continue;
        }
        
        int num = toupper(c) - 'A'; // A=0, B=1, ..., Z=25
        const auto& key = keys[key_index++];
        
        int encrypted = (key[0] * num + key[1]) % ALPHABET_SIZE;
        if (encrypted < 0) encrypted += ALPHABET_SIZE;
        
        result += static_cast<char>('A' + encrypted);
    }
    
    return result;
}

std::vector<std::array<int, 2>> AffineRecurrentCipher::decryption_keys(
    const std::vector<std::array<int, 2>>& encryption_keys) 
{
    std::vector<std::array<int, 2>> dec_keys;
    
    for (const auto& key : encryption_keys) {
        int a = key[0];
        int b = key[1];
        
        int a_inv = SubstitutionCipher::opposite_alpha(a);
        // Проверка корректности обратного элемента
        if ((a * a_inv) % ALPHABET_SIZE != 1) {
            throw std::invalid_argument("Invalid key - no modular inverse");
        }
        
        dec_keys.push_back({a_inv, b});  // Сохраняем b для использования в формуле
    }
    
    return dec_keys;
}

std::string AffineRecurrentCipher::decryption(const std::string& ciphertext, 
                                            const std::array<int, 2>& key1,
                                            const std::array<int, 2>& key2) 
{
    if (ciphertext.empty()) return "";

    auto enc_keys = all_keys(key1, key2, ciphertext);
    auto dec_keys = decryption_keys(enc_keys);
    std::string result;
    size_t key_index = 0;
    
    for (char c : ciphertext) {
        if (c == ' ') {
            result += ' ';
            continue;
        }
        
        int num = toupper(c) - 'A';
        const auto& key = dec_keys[key_index++];
        
        // Правильная формула дешифрования: D(x) = a⁻¹(x - b) mod 26
        int decrypted = (key[0] * (num - key[1])) % ALPHABET_SIZE;
        decrypted = (decrypted + ALPHABET_SIZE) % ALPHABET_SIZE;
        
        result += static_cast<char>('A' + decrypted);
    }
    
    return result;
}