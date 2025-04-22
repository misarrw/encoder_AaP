# include "VigenereCipher.hpp"
# include <vector>
# include <string>


class OpentextGamma : public VigenereCipher
{
public: 
    std::vector<int> opentext(const std::string& key, std::vector<int>& text_numbers, int option);
};