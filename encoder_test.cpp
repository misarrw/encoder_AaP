#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "SubFunctions.hpp"
#include "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.hpp"
#include "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.hpp"

extern const std::string ALPHABET;

TEST_CASE("Encoding tests") {
    SubFunction encoder;
    
    SUBCASE("Space encoding") {
        CHECK(encoder.text_in_numbers(" ") == std::vector<int>{-1});
    }
    
    SUBCASE("Letters encoding") {
        CHECK(encoder.text_in_numbers("ABCD") == std::vector<int>{1, 2, 3, 4});
    }
    
    SUBCASE("Mixed input") {
        CHECK(encoder.text_in_numbers("A B") == std::vector<int>{1, -1, 2});  
    }
    
    SUBCASE("Sentence encoding") {
        CHECK(encoder.text_in_numbers("Hello world") == std::vector<int>{8, 5, 12, 12, 15, -1, 23, 15, 18, 12, 4});
    }
}

TEST_CASE("Creating rep gamma") {
    VigenereCipher::RepetitionGamma gamma;

    SUBCASE("Short key repeats correctly") {
        std::string key = "AB";
        std::vector<int> text_numbers{1,1,1}; 
        CHECK(gamma.repgamma(key, text_numbers) == std::vector<int>{1, 2, 1}); 
    }

    SUBCASE("Key same length as text") {
        std::string key = "XYZ";
        std::vector<int> text_numbers{1,1,1};
        CHECK(gamma.repgamma(key, text_numbers) == std::vector<int>{24, 25, 26}); 
    }

    SUBCASE("Single-letter key") {
        std::string key = "A";
        std::vector<int> text_numbers{1,1,1};
        CHECK(gamma.repgamma(key, text_numbers) == std::vector<int>{1,1,1});
    }
}

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
        // Используем ключи, где a взаимно просты с 26
        std::array<int, 2> key1 = {5, 7};   // 5 и 26 взаимно просты
        std::array<int, 2> key2 = {7, 11};  // 7 и 26 взаимно просты
        std::string text = "H E";
        
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        CHECK(encrypted == "Q N");
    }

    // ... остальные тесты

    SUBCASE("Empty input") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "";
        
        std::string encrypted = cipher.encryption(text, key1, key2);
        CHECK(encrypted == "");
    }

    SUBCASE("Invalid keys") {
        std::array<int, 2> key1 = {2, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "TEST";
        
        CHECK_THROWS_AS(cipher.encryption(text, key1, key2), std::invalid_argument);
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