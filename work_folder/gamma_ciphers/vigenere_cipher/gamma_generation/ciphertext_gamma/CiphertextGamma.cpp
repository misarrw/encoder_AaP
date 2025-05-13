# include "CiphertextGamma.h"
# include "../../../../globals.h"
# include <iostream>
# include <vector>
# include <string>

std::vector<int> CiphertextGamma::ciphertext(const std::string& key){
    std::vector<int> gamma{};
    gamma.push_back(ALPHABET.find(key[0]));
    return gamma;
}