#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "globals.h"
#include "SubFunctions.h"
#include "work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.h"
#include "work_folder/substitution_ciphers/affine/AffineCipher.h"
#include "work_folder/substitution_ciphers/caesar/CaesarCipher.h"
#include "work_folder/block_ciphers/hill_cipher/HillCipher.h"
#include "work_folder/block_ciphers/hill_recurrent/HillRecurrentCipher.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereRepetitionGamma/VigenereRepetitionGamma.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereOpenTextGamma/VigenereOpenTextGamma.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereCipherTextGamma/VigenereCipherTextGamma.h"
#include "work_folder/gamma_ciphers/GammaCipher.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.h"
#include "work_folder/gamma_ciphers/VernameCipher/VernameCipher.h"
#include <memory>

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

TEST_CASE("Affine recurrent encryption and decryption") {
    SUBCASE("Basic encryption") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO";
        char option = '1';
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, option);
        CHECK(encrypted == "QNNUD");
    }

    SUBCASE("With spaces") {
        std::array<int, 2> key1 = {5, 7};   
        std::array<int, 2> key2 = {7, 11};  
        std::string text = "H E";
        char option = '1';        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, option);
        CHECK(encrypted == "Q N");
    }

    SUBCASE("Empty input") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "";
        char option = '1';
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, option);
        CHECK(encrypted == "");
    }

    SUBCASE("Case conversion") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "Hello";
        char option = '1';
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, option);
        CHECK(encrypted == "QNNUD");
    }

    SUBCASE("Full cycle") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO WORLD";
        char encrypted_choice = '1';
        char decrypted_choice = '2';
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, encrypted_choice);
        std::string decrypted = arcipher.cipher(encrypted, decrypted_choice);
        
        CHECK(encrypted == "QNNUD KVGVW");
        CHECK(decrypted == "HELLO WORLD");
    }

    SUBCASE("All letters") {
        std::array<int, 2> key1 = {3, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char encrypted_choice = '1';
        char decrypted_choice = '2';
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, encrypted_choice);
        std::string decrypted = arcipher.cipher(encrypted, decrypted_choice);

        
        CHECK(decrypted == text);
    }

    SUBCASE("Multiple spaces") {
        std::array<int, 2> key1 = {3, 5};
        std::array<int, 2> key2 = {7, 10};
        std::string text = "A  B   C";
        char encrypted_choice = '1';
        char decrypted_choice = '2';
        
        AffineRecurrentCipher arcipher(key1, key2);
        std::string encrypted = arcipher.cipher(text, encrypted_choice);
        std::string decrypted = arcipher.cipher(encrypted, decrypted_choice);
        
        CHECK(decrypted == text);
    }

    SUBCASE("Invalid choice") {
        std::array<int, 2> key1 = {5, 7};
        std::array<int, 2> key2 = {7, 11};
        std::string text = "HELLO";
        char option = '3';

        AffineRecurrentCipher arcipher(key1, key2);
        CHECK_THROWS_AS(arcipher.cipher(text, option), std::invalid_argument);
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
        char option = '1';
        std::string encrypted = cipher.hill(text, option);
        CHECK(encrypted == "WWH"); 
    }
    
    SUBCASE("Decrypt short text") {
        std::string text = "WWH";
        char option = '2';
        std::string decrypted = cipher.hill(text, option);
        CHECK(decrypted == "HEL");
    }
    
    SUBCASE("Encrypt with padding") {
        std::string text = "HE";
        char option = '1';
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
        char encrypt_option = '1';
        char decrypt_option = '2';
        std::string encrypted = cipher.hill(original, encrypt_option);
        std::string decrypted = cipher.hill(encrypted, decrypt_option);
        
        CHECK(decrypted == original);
    }
    
    SUBCASE("Case insensitivity") {
        std::string upper = "HELLO";
        std::string mixed = "HeLlO";
        char encrypt_option = '1';
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
        
        CHECK(new_key[0][0] == (2*11 + 3*17) % 26);
        CHECK(new_key[0][1] == (2*13 + 3*19) % 26);
        CHECK(new_key[1][0] == (5*11 + 7*17) % 26);
        CHECK(new_key[1][1] == (5*13 + 7*19) % 26);
    }

}

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
TEST_CASE("AffineEncoder encrypts characters correctly") {
    AffineCoder coder(5, 8);  
    int index = 0; 
    int result = coder.cipher(index);
    CHECK(result == (5 * 0 + 8) % 26); 
}

TEST_CASE("AffineCoder decrypts characters correctly") {
    AffineCoder coder(5, 8);
    AffineEncoder encoder(5, 8);

    int original = 0; // 'A'
    int encrypted = coder.cipher(original);

    int decrypted = encoder.cipher(encrypted);
    CHECK(decrypted == original);
}

TEST_CASE("AffineCipher end-to-end encryption") {
    std::string text = "HELLO";
    AffineCipher cipher(text);

    AffineCoder coder(5, 8);
    std::string encrypted = cipher.affine(coder);

    CHECK(encrypted.size() == text.size());
    for (char c : encrypted) {
        CHECK(isupper(c)); 
    }
}

TEST_CASE("AffineEncoder throws on invalid alpha") {
    int bad_alpha = 13; 
    int beta = 5;
    AffineCoder coder(bad_alpha, beta);
    int index = 0;
    int encrypted = coder.cipher(index);
    CHECK(encrypted == (13 * 0 + 5) % 26); 
}