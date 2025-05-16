#include <iostream>
#include "SubFunctions.h"
#include "globals.h"
#include "algorithm"

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

int SubFunction::extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int SubFunction::modInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);
    
    if (gcd != 1) {
        return -1; 
    } else {
        return (x % m + m) % m;
    }
}

bool SubFunction::is_alpha(const std::string& str) {
    return !str.empty() && 
           std::all_of(str.begin(), str.end(), 
               [](char c){ return isalpha(c); });
}