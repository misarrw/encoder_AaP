#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "SubFunctions.h"
#include "work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.h"
#include "globals.h"
#include "work_folder/substitution_ciphers/caesar/CaesarCipher.h"
#include "work_folder/block_ciphers/hill_cipher/HillCipher.h"
#include "work_folder/block_ciphers/hill_recurrent/HillRecurrentCipher.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereRepetitionGamma/VigenereRepetitionGamma.h"
#include "work_folder/gamma_ciphers/GammaCipher.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.h"

// sardarik's tests
TEST_CASE("Encoding tests") {
    SubFunction encoder;
    
    SUBCASE("Space encoding") {
        CHECK(encoder.text_in_numbers(" ") == std::vector<int>{-1});
    }
    
    SUBCASE("Letters encoding") {
        CHECK(encoder.text_in_numbers("ABCD") == std::vector<int>{0, 1, 2, 3});
    }
    
    SUBCASE("Mixed input") {
        CHECK(encoder.text_in_numbers("A B") == std::vector<int>{0, -1, 1});  
    }
    
    SUBCASE("Sentence encoding") {
        CHECK(encoder.text_in_numbers("Hello world") == std::vector<int>{7, 4, 11, 11, 14, -1, 22, 14, 17, 11, 3});
    }
}

// TEST_CASE("Creating rep gamma") {
//     ViginereRepetitionGamma gamma;

//     SUBCASE("Short key repeats correctly") {
//         std::string key = "AB";
//         std::vector<int> text_numbers{1,1,1}; 
//         CHECK(gamma.repgamma(key, text_numbers) == std::vector<int>{0, 1, 0}); 
//     }

//     SUBCASE("Key same length as text") {
//         std::string key = "XYZ";
//         std::vector<int> text_numbers{1,1,1};
//         CHECK(gamma.repgamma(key, text_numbers) == std::vector<int>{23, 24, 25}); 
//     }

//     SUBCASE("Single-letter key") {
//         std::string key = "A";
//         std::vector<int> text_numbers{1,1,1};
//         CHECK(gamma.repgamma(key, text_numbers) == std::vector<int>{0,0,0});
//     }
// }

// TEST_CASE("VigenereRepetitionGamma - Creating repetition gamma") {
//     SUBCASE("Short key repeats correctly") {
//         std::string text = 'BBBB';
//         int option = 1;
//         VigenereRepetitionGamma gamma(text, option);
//         std::string key = "AB";
//         std::vector<int> expected{0, 1, 0, 1}; // A=0, B=1, A=0, B=1
//         CHECK(gamma()) == expected);
//     }
    
    // SUBCASE("Key same length as text") {
    //     std::string key = "XYZ";
    //     std::vector<int> text_numbers{1, 1, 1};
    //     std::vector<int> expected{23, 24, 25}; // X=23, Y=24, Z=25
    //     CHECK(gamma.repgamma(key, text_numbers) == expected);
    // }
    
    // SUBCASE("Single-letter key") {
    //     std::string key = "A";
    //     std::vector<int> text_numbers{1, 1, 1, 1, 1};
    //     std::vector<int> expected{0, 0, 0, 0, 0}; // A=0 repeated
    //     CHECK(gamma.repgamma(key, text_numbers) == expected);
    // }
    
    // SUBCASE("Empty key throws exception") {
    //     std::string key = "";
    //     std::vector<int> text_numbers{1, 2, 3};
    //     CHECK_THROWS_AS(gamma.repgamma(key, text_numbers), std::invalid_argument);
    // }
    
    // SUBCASE("Non-alphabetic key throws exception") {
    //     std::string key = "A1B";
    //     std::vector<int> text_numbers{1, 2, 3};
    //     CHECK_THROWS_AS(gamma.repgamma(key, text_numbers), std::invalid_argument);
    // }
    
    // SUBCASE("Mixed case key works correctly") {
    //     std::string key = "aBc";
    //     std::vector<int> text_numbers{1, 1, 1};
    //     std::vector<int> expected{0, 1, 2}; // a=0, B=1, c=2
    //     CHECK(gamma.repgamma(key, text_numbers) == expected);
    // }
// }




TEST_CASE("Affine recurrent encryption and decryption") {
    SUBCASE("Basic encryption") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO";
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        CHECK(encrypted == "QNNUD");
    }

    SUBCASE("With spaces") {
        std::array<int, 2> key1 = {5, 7};   
        std::array<int, 2> key2 = {7, 11};  
        std::string text = "H E";        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        CHECK(encrypted == "Q N");
    }

    SUBCASE("Empty input") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "";
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        CHECK(encrypted == "");
    }

    SUBCASE("Case conversion") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "Hello";
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        CHECK(encrypted == "QNNUD");
    }

    SUBCASE("Full cycle") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO WORLD";
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        std::string decrypted = arcipher.cipher(encrypted, 2);
        
        CHECK(encrypted == "QNNUD KVGVW");
        CHECK(decrypted == "HELLO WORLD");
    }

    SUBCASE("All letters") {
        std::array<int, 2> key1 = {3, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        std::string decrypted = arcipher.cipher(encrypted, 2);

        
        CHECK(decrypted == text);
    }

    SUBCASE("Multiple spaces") {
        std::array<int, 2> key1 = {3, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "A  B   C";
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, 1);
        std::string decrypted = arcipher.cipher(encrypted, 2);
        
        CHECK(decrypted == text);
    }

    SUBCASE("Invalid choice") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO";

        AffineRecurrentCipher arcipher(key1, key2);
        CHECK_THROWS_AS(arcipher.cipher(text, 3), std::invalid_argument);
    }

    SUBCASE("Invalid characters") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO!";
        AffineRecurrentCipher arcipher(key1, key2);
        
        
        CHECK_THROWS_AS(arcipher.cipher(text, 1), std::invalid_argument);
    }
}

TEST_CASE("Hill Recurrent Cipher - Basic Encryption/Decryption") {
    std::vector<std::vector<int>> key1 = {
        {1, 2, 3},
        {0, 1, 4}, 
        {5, 6, 0}  
    };
    std::vector<std::vector<int>> key2 = {
        {2, 4, 5},
        {3, 1, 2},
        {6, 3, 1}  
    };
    HillRecurrentCipher cipher(key1, key2);
    
    SUBCASE("Encrypt short text") {
        std::string text = "HEL";
        int option = 1;
        std::string encrypted = cipher.hill(text, option);
        CHECK(encrypted == "WWH"); 
    }
    
    SUBCASE("Decrypt short text") {
        std::string text = "WWH";
        int option = 2;
        std::string decrypted = cipher.hill(text, option);
        CHECK(decrypted == "HEL");
    }
    
    SUBCASE("Encrypt with padding") {
        std::string text = "HE";
        int option = 1;
        std::string encrypted = cipher.hill(text, option);
        CHECK(encrypted.size() == 3); 
    }
}

TEST_CASE("Hill Recurrent Cipher - Key Generation") {
    std::vector<std::vector<int>> key1 = {{2, 3}, {5, 7}};
    std::vector<std::vector<int>> key2 = {{11, 13}, {17, 19}};
    HillRecurrentCipher cipher(key1, key2);
    
    SUBCASE("Generate next key") {
        auto new_key = cipher.generate_next_key(key1, key2);
        
        // Проверяем правильность генерации следующего ключа
        CHECK(new_key[0][0] == (2*11 + 3*17) % 26);
        CHECK(new_key[0][1] == (2*13 + 3*19) % 26);
        CHECK(new_key[1][0] == (5*11 + 7*17) % 26);
        CHECK(new_key[1][1] == (5*13 + 7*19) % 26);
    }
    
}


TEST_CASE("Hill Recurrent Cipher - Full Cycle") {
    std::vector<std::vector<int>> key1 = {{1, 11}, {0, 1}};
    std::vector<std::vector<int>> key2 = {{1, 0}, {11, 1}};
    HillRecurrentCipher cipher(key1, key2);
    
    SUBCASE("Encrypt-Decrypt cycle") {
        std::string original = "SECRETSMESSAGE";
        int encrypt_option = 1;
        int decrypt_option = 2;
        std::string encrypted = cipher.hill(original, encrypt_option);
        std::string decrypted = cipher.hill(encrypted, decrypt_option);
        
        CHECK(decrypted == original);
    }
    
    SUBCASE("Case insensitivity") {
        std::string upper = "HELLO";
        std::string mixed = "HeLlO";
        int encrypt_option = 1;
        std::string encrypted_upper = cipher.hill(upper, encrypt_option);
        std::string encrypted_mixed = cipher.hill(mixed, encrypt_option);
        
        CHECK(encrypted_upper == encrypted_mixed);
    }
}


TEST_CASE("Hill Recurrent Cipher - Matrix Operations") {
    SUBCASE("Matrix multiplication and modulo") {
        std::vector<std::vector<int>> key1 = {{2, 3}, {5, 7}};
        std::vector<std::vector<int>> key2 = {{11, 13}, {17, 19}};
        HillRecurrentCipher cipher(key1, key2);
        
        auto new_key = cipher.generate_next_key(key1, key2);
        
        // Проверяем правильность умножения матриц и применения модуля
        CHECK(new_key[0][0] == (2*11 + 3*17) % 26);
        CHECK(new_key[0][1] == (2*13 + 3*19) % 26);
        CHECK(new_key[1][0] == (5*11 + 7*17) % 26);
        CHECK(new_key[1][1] == (5*13 + 7*19) % 26);
    }

}


// // misarrw's tests
// TEST_CASE("Caesar encryption") {
//     std::string k = "qazwsxedcrfvtgbyhnujmikolp";
//     CaesarCipher caesar(k);

//     SUBCASE("Empty string") {
//         std::string text = "";
//         std::string ciphertext = caesar.caesar_encryption(text);
//         CHECK(ciphertext == "");
//     }

//     SUBCASE("One-symbol string") {
//         std::string text = "A";
//         std::string ciphertext = caesar.caesar_encryption(text);
//         CHECK(ciphertext == "Q");
//     }

//     SUBCASE("Different letter cases string") {
//         std::string text = "bUtTeRfLy";
//         std::string ciphertext = caesar.caesar_encryption(text);
//         CHECK(ciphertext == "AMJJSNXVL");
//     }

//     SUBCASE("Letters and symbols string") {
//         std::string text = "Hello, World!";
//         std::string ciphertext = caesar.caesar_encryption(text);
//         CHECK(ciphertext == "DSVVB, KBNVW!");
//     }
// }


// TEST_CASE("Caesar Decryption") {
//     std::string k = "qazwsxedcrfvtgbyhnujmikolp";
//     CaesarCipher caesar(k);

//     SUBCASE("Empty string") {
//         std::string ciphertext = "";
//         std::string text = caesar.caesar_decryption(ciphertext);
//         CHECK(text == "");
//     }

//     SUBCASE("One-symbol string") {
//         std::string ciphertext = "Q";
//         std::string text = caesar.caesar_decryption(ciphertext);
//         CHECK(text == "A");
//     }

//     SUBCASE("Different letter cases string") {
//         std::string ciphertext = "AmJjSnXvL";
//         std::string text = caesar.caesar_decryption(ciphertext);
//         CHECK(text == "BUTTERFLY");
//     }

//     SUBCASE("Letters and symbols string") {
//         std::string ciphertext = "Dsvvb, Kbnvw!";
//         std::string text = caesar.caesar_decryption(ciphertext);
//         CHECK(text == "HELLO, WORLD!");
//     }
// }


// TEST_CASE("Caesar invalid key") {
//     SUBCASE("Not full key") {
//         REQUIRE_THROWS_AS(CaesarCipher{"hahaha"}, std::invalid_argument);
//     }

//     SUBCASE("Repeated symbols key") {
//         REQUIRE_THROWS_AS(CaesarCipher{"aaaaaaaaaaaaaaaaaaaaaaaaaa"}, std::invalid_argument);
//     }

//     SUBCASE("Empty key") {
//         REQUIRE_THROWS_AS(CaesarCipher{""}, std::invalid_argument);
//     }

//     SUBCASE("Key with symbols") {
//         REQUIRE_THROWS_AS(CaesarCipher{"ABC123?"}, std::invalid_argument);
//     }
// }


// TEST_CASE("Vigenere encryption") {
//     std::vector<std::vector<int>> key{{1, 1}, {3, 4}};
//     std::unique_ptr<BlockCipher> key_vec = std::make_unique<HillCipher>(key);
//     int option = 1;

//     SUBCASE("Empty string") {
//         std::string text = "";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "");
//     }

//     SUBCASE("One-symbol string") {
//         std::string text = "A";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "XO");
//     }

//     SUBCASE("Different letter cases string") {
//         std::string text = "bUtTeRfLy";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "VFMDVCQHVI");
//     }

//     SUBCASE("Letters and symbols string") {
//         std::string text = "Hello, World!";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "LLWZNMKSCRAX");
//     }
// }


// TEST_CASE("Vigenere decryption") {
//     std::vector<std::vector<int>> key{{1, 1}, {3, 4}};
//     std::unique_ptr<BlockCipher> key_vec = std::make_unique<HillCipher>(key);
//     int option = 2;

//     SUBCASE("Empty string") {
//         std::string text = "";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "");
//     }

//     SUBCASE("One-symbol string") {
//         std::string text = "A";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "DX");
//     }

//     SUBCASE("Different letter cases string") {
//         std::string text = "VfMdVcQhVi";
//         std::string ciphertext = key_vec->hill(text, option);
//         CHECK(ciphertext == "BUTTERFLYX");
//     }
// }


// TEST_CASE("Hill invalid key") {
//     SUBCASE("Not square matrix") {
//         REQUIRE_THROWS_AS(BlockCipher({{1, 1}, {1}}), std::invalid_argument);
//     }

//     SUBCASE("no GCD = 1") {
//         REQUIRE_THROWS_AS(BlockCipher({{1, 1}, {3, 5}}), std::invalid_argument);
//     }
// }


// jabohka's tests