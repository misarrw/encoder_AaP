#include <iostream>
#include <array>
#include <string>
#include <numeric>
#include "../../globals.h"
#include "AffineRecurrentCipher.h"
#include "../../../work_folder/SubFunctions.h"
#include "../../../work_folder/substitution_ciphers/SubstitutionCipher.h"

std::array<int, 2> AffineRecurrentCipher::find_another_key(const std::array<int, 2>& key1, 
                                                         const std::array<int, 2>& key2)
{
    return {
        (key1[0] * key2[0]) % ALPHABET_SIZE, 
        (key1[1] + key2[1]) % ALPHABET_SIZE
    };
}

std::string AffineRecurrentCipher::cipher(const std::string& text, 
                                        const int choice) 
{
    if (text.empty()) return "";

    std::vector<int> pre_result;
    std::array<int, 2> current_key, next_key;
    
    if (choice == 1) { 
        current_key = key1;
        next_key = key2;
    } 
    else if (choice == 2) { 
        int tmp_a1 = key1[0];
        int tmp_a2 = key2[0];
        current_key = {
            SubstitutionCipher::opposite_alpha(tmp_a1),
            key1[1]  
        };
        next_key = {
            SubstitutionCipher::opposite_alpha(tmp_a2),
            key2[1]  
        };
    }
    else {
        throw std::invalid_argument("Invalid choice value. Use 1 for encryption or 2 for decryption");
    }

    for (char c : text) {
        char upper = std::toupper(static_cast<unsigned char>(c));
        int num;
        if (upper == ' ') {
            pre_result.push_back(-1); 
            continue;
        }
        size_t pos = ALPHABET.find(upper);
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid character: " + std::string(1, c)); // change to is_alpha
        }
        num = static_cast<int>(pos);

        int modified;
        if (choice == 1) { 
            modified = (current_key[0] * num + current_key[1]) % ALPHABET_SIZE;
        } 
        else { 
            modified = (current_key[0] * (num - current_key[1])) % ALPHABET_SIZE;
        }
        
        if (modified < 0) modified += ALPHABET_SIZE;
        pre_result.push_back(modified);

        auto new_key = find_another_key(current_key, next_key);
        current_key = next_key;
        next_key = new_key;
    }

    std::string result = SubFunction::numbers_to_text(pre_result);
    
    return result;
}