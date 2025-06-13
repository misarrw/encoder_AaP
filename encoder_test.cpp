#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "SubFunctions.h"
#include "work_folder\substitution_ciphers\affine_recurrent\AffineRecurrentCipher.h"
#include "globals.h"
#include "work_folder\substitution_ciphers\caesar\CaesarCipher.h"
#include "work_folder\block_ciphers\hill_cipher\HillCipher.h"


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
//     RepetitionGamma gamma;

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

TEST_CASE("Affine recurrent encryption and decryption") {
    AffineRecurrentCipher cipher;
    
    SUBCASE("Basic encryption") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        CHECK(encrypted == "QNNUD");
    }


    SUBCASE("With spaces") {
        std::array<int, 2> key1 = {5, 7};   
        std::array<int, 2> key2 = {7, 11};  
        std::string text = "H E";
        
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        CHECK(encrypted == "Q C");
    }


    SUBCASE("Empty input") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        CHECK(encrypted == "");
    }


    SUBCASE("Case conversion") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "Hello";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        CHECK(encrypted == "QNNUD");
    }

    SUBCASE("Full cycle") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO WORLD";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        std::string decrypted = cipher.decryption(encrypted, key1, key2);
        
        CHECK(encrypted == "QNNUD LLBAG");
        CHECK(decrypted == "HELLO WORLD");
    }

    SUBCASE("All letters roundtrip") {
        std::array<int, 2> key1 = {3, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        std::string decrypted = cipher.decryption(encrypted, key1, key2);
        
        CHECK(decrypted == text);
    }

    SUBCASE("Multiple spaces") {
        std::array<int, 2> key1 = {3, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "A  B   C";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        std::string decrypted = cipher.decryption(encrypted, key1, key2);
        
        CHECK(decrypted == text);
    }
}


// misarrw's tests
TEST_CASE("Caesar encryption") {
    std::string k = "qazwsxedcrfvtgbyhnujmikolp";
    CaesarCipher caesar(k);

    SUBCASE("Empty string") {
        std::string text = "";
        std::string ciphertext = caesar.caesar_encryption(text);
        CHECK(ciphertext == "");
    }

    SUBCASE("One-symbol string") {
        std::string text = "A";
        std::string ciphertext = caesar.caesar_encryption(text);
        CHECK(ciphertext == "Q");
    }

    SUBCASE("Different letter cases string") {
        std::string text = "bUtTeRfLy";
        std::string ciphertext = caesar.caesar_encryption(text);
        CHECK(ciphertext == "AMJJSNXVL");
    }

    SUBCASE("Letters and symbols string") {
        std::string text = "Hello, World!";
        std::string ciphertext = caesar.caesar_encryption(text);
        CHECK(ciphertext == "DSVVB, KBNVW!");
    }
}


TEST_CASE("Caesar Decryption") {
    std::string k = "qazwsxedcrfvtgbyhnujmikolp";
    CaesarCipher caesar(k);

    SUBCASE("Empty string") {
        std::string ciphertext = "";
        std::string text = caesar.caesar_decryption(ciphertext);
        CHECK(text == "");
    }

    SUBCASE("One-symbol string") {
        std::string ciphertext = "Q";
        std::string text = caesar.caesar_decryption(ciphertext);
        CHECK(text == "A");
    }

    SUBCASE("Different letter cases string") {
        std::string ciphertext = "AmJjSnXvL";
        std::string text = caesar.caesar_decryption(ciphertext);
        CHECK(text == "BUTTERFLY");
    }

    SUBCASE("Letters and symbols string") {
        std::string ciphertext = "Dsvvb, Kbnvw!";
        std::string text = caesar.caesar_decryption(ciphertext);
        CHECK(text == "HELLO, WORLD!");
    }
}


TEST_CASE("Caesar invalid key") {
    std::stringstream buffer;
    auto* old_buf = std::cerr.rdbuf(buffer.rdbuf());
    SUBCASE("Not full key") {
        CaesarCipher caesar("hahaha");
        std::cerr.rdbuf(old_buf);
        std::string output = buffer.str();
        REQUIRE(output.find("Error: Your key is too short or incorrect. Check the tip and try again"));
    }

    SUBCASE("Repeated symbols key") {
        CaesarCipher caesar("aaaaaaaaaaaaaaaaaaaaaaaaaa");
        std::cerr.rdbuf(old_buf);
        std::string output = buffer.str();
        REQUIRE(output.find("Error: Your key is too short or incorrect. Check the tip and try again"));
    }

    SUBCASE("Empty key") {
        CaesarCipher caesar("");
        std::cerr.rdbuf(old_buf);
        std::string output = buffer.str();
        REQUIRE(output.find("Error: Your key is too short or incorrect. Check the tip and try again"));
    }

    SUBCASE("Key with symbols") {
        CaesarCipher caesar("ABC123?");
        std::cerr.rdbuf(old_buf);
        std::string output = buffer.str();
        REQUIRE(output.find("Error: Your key is too short or incorrect. Check the tip and try again"));
    }
}


TEST_CASE("Hill encryption") {
    std::vector<std::vector<int>> key{{1, 1}, {3, 4}};
    std::unique_ptr<BlockCipher> key_vec = std::make_unique<HillCipher>(key);
    char option = '1';

    SUBCASE("Empty string") {
        std::string text = "";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "");
    }

    SUBCASE("One-symbol string") {
        std::string text = "A";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "XO");
    }

    SUBCASE("Different letter cases string") {
        std::string text = "bUtTeRfLy";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "VFMDVCQHVI");
    }

    SUBCASE("Letters and symbols string") {
        std::string text = "Hello, World!";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "LLWZNMKSCRAX");
    }
}


TEST_CASE("Hill decryption") {
    std::vector<std::vector<int>> key{{1, 1}, {3, 4}};
    std::unique_ptr<BlockCipher> key_vec = std::make_unique<HillCipher>(key);
    char option = '2';

    SUBCASE("Empty string") {
        std::string text = "";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "");
    }

    SUBCASE("One-symbol string") {
        std::string text = "A";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "DX");
    }

    SUBCASE("Different letter cases string") {
        std::string text = "VfMdVcQhVi";
        std::string ciphertext = key_vec->hill(text, option);
        CHECK(ciphertext == "BUTTERFLYX");
    }
}


TEST_CASE("Hill invalid key") {
    std::stringstream buffer;
    auto* old_buf = std::cerr.rdbuf(buffer.rdbuf());
    SUBCASE("Not square matrix") {
        BlockCipher key_vec({{1, 1}, {1}});
        std::cerr.rdbuf(old_buf);
        std::string output = buffer.str();
        REQUIRE(output.find("Your matrix is not square :("));
    }

    SUBCASE("no GCD = 1") {
        BlockCipher key_vec({{1, 1}, {1}});
        std::cerr.rdbuf(old_buf);
        std::string output = buffer.str();
        REQUIRE(output.find("Error: Remember the GCD rules! The determinant of your matrix-key should have 1 as GCD with the number of the letters in your language. Try again:"));
    }
}


// jabohka's tests