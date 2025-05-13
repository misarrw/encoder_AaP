#pragma once
#include "..\VigenereCipher.h"

class VigenereOpenTextGamma : public VigenereCipher {
    protected:
    size_t len_key = 1;
    void creat_gamma() override;
};
