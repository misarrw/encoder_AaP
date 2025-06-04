#pragma once
#include <..\SubstitutionCipher.h> 
#include <array>

class AffineCipher: public SubstitutionCipher
{
    public:
        std::string text;
        int alpha;
        int beta;
        bool flag;

        std::string affine();
        int cipher(int &index);
        AffineCipher(const char& alpha, const char& beta, const std::string& text, bool flag);
};

class AffineCoder: public AffineCipher
{
    public:
        int cipher(int &index);     
        AffineCoder();
};

class AffineEncoder: public AffineCipher
{
    public:
        int cipher(int &index);
        AffineEncoder();
};
