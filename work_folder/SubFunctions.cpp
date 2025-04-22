#include <iostream>
#include "SubFunctions.hpp"
#include "globals.hpp"
#include <cctype>

std::vector<int> SubFunction::text_in_numbers(const std::string& text) {
    std::vector<int> result;
    
    for (char letter : text) {
        char upper_letter = std::toupper(static_cast<unsigned char>(letter));
        

        if (upper_letter == ' ') {
            result.push_back(0);
            result.push_back(0);
            continue;
        }
        
        size_t letter_pos = ALPHABET.find(upper_letter);
        if (letter_pos != std::string::npos) {
            result.push_back(static_cast<int>(letter_pos) + 1); 
            continue;
        }

        size_t symbol_pos = SYMBOLS.find(upper_letter);
        if (symbol_pos != std::string::npos) {
            result.push_back(static_cast<int>(symbol_pos) + 100); 
        }
    }
    
    return result;
}