#include "SubstitutionCipher.hpp"
#include <array>
#include <string>

class AffineRecurrentCipher : public SubstitutionCipher
{
public:
    std::array<int, 2> find_another_key(const std::array<int, 2>& key1, const std::array<int, 2>& key2, const std::string& text);
};