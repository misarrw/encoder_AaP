#include <iostream>
#include "CaesarCipher.h"
#include <cctype>
#include "AffineRecurrentCipher.h"
#include "work_folder/SubFunctions.h"

int main()
{
    std::string t = "hello world";
    std::string t1 = "QNNUD LLBAG";
    std::array<int, 2> k1{5,7};
    std::array<int, 2> k2{7,11};
    AffineRecurrentCipher cipher;
    std::cout << cipher.encryption(t, k1, k2) << std::endl;
    std::cout << cipher.decryption(t1, k1, k2) << std::endl;
    // std::vector<std::array<int,2>> keys = cipher.all_keys(k1, k2, t);
    // std::cout << "Generated keys: ";
    // for (const auto& key : keys) {
    //     std::cout << "[" << key[0] << "," << key[1] << "] ";
    // }
    // std::cout << std::endl;
    

    std::vector<int> numbers = SubFunction::text_in_numbers(t1);
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << SubFunction::numbers_to_text(numbers) << std::endl;

    return 0;
}