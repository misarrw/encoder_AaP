#pragma once
#include "..\VigenereCipher.h"

class VigenereRepetitionGamma : public VigenereCipher {
    protected:
    size_t len_key = text_numbers.size();
    void creat_gamma() override;
};
