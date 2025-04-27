#include <iostream>
#include "SubFunctions.h"
#include "globals.h"
#include <cctype>

std::vector<int> SubFunction::text_in_numbers(const std::string& text) {
    std::vector<int> result;
    
    for (char letter : text) {
        char upper_letter = std::toupper(static_cast<unsigned char>(letter));

        if (upper_letter == ' ') {
            result.push_back(-1);
            continue;
        }
        
        size_t letter_pos = ALPHABET.find(upper_letter);
        if (letter_pos != std::string::npos) {
            result.push_back(static_cast<int>(letter_pos)); 
            continue;
        }
    }
    
    return result;
}

std::string SubFunction::numbers_to_text(const std::vector<int>& nums) {
    std::string result;
    for (int num : nums) {
        if (num == -1) {
            result += ' ';
        } else {
            result += static_cast<char>('A' + num);
        }
    }
    return result;
}