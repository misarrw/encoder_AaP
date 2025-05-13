# pragma once
# include "..\..\VigenereCipher.h"
# include <vector>
# include <string>


class CipherextGamma : public VigenereCipher
{
    public: 
        std::vector<int> ciphertext(const std::string& key);
};
