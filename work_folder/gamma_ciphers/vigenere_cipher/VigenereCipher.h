#pragma once
#include <vector>
#include <string>

class VigenereCipher {
public:
    virtual ~VigenereCipher() = default;  

    class RepetitionGamma {
    public:
        std::vector<int> repgamma(const std::string& key, std::vector<int>& text_numbers);
    };

    class OpentextGamma {
    public:
        std::vector<int> opentext(const std::string& key, std::vector<int>& text_numbers, int option);
    };

    class CiphertextGamma {
    public:
        std::vector<int> ciphertext(const std::string& key);
    };
    // Дополнительно можно сделать экземпляры классов полями:
    RepetitionGamma repetitionGamma;
    OpentextGamma opentextGamma;
};