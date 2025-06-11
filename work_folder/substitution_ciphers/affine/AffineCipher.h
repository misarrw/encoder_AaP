#pragma once
#include "..\SubstitutionCipher.h"
#include <array>

class Affine
{
    public:
    virtual int cipher(int &index) = 0;
    int alpha;
    int beta;
    Affine(int alpha, int beta): alpha(alpha), beta(beta) {} 
    virtual ~Affine() {}
};

class AffineCipher: public SubstitutionCipher
{
    public:
        std::string text;
        std::string affine(Affine& coder);
        AffineCipher(const std::string& text);
};

class AffineCoder: public Affine
{
    public:
        AffineCoder(int alpha, int beta) : Affine(alpha, beta){}
        int cipher(int &index) override;
};

class AffineEncoder: public Affine
{
    public:
    AffineEncoder(int alpha, int beta) : Affine(alpha, beta){}
    int cipher(int &index) override;
};