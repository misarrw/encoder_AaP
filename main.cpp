/**
 * \file
 * \brief Точка входа в приложение. Обеспечивает пользовательский интерфейс для запуска различных шифров.
 */

#include <iostream>
#include <cctype>
#include "work_folder/SubFunctions.h"
#include "work_folder/substitution_ciphers/caesar/CaesarCipher.h"
#include "work_folder/substitution_ciphers/affine/AffineCipher.h"
#include "work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.h"
#include "work_folder/files_functions.h"
#include "work_folder/block_ciphers/BlockCipher.h"
#include "work_folder/block_ciphers/hill_cipher/HillCipher.h"
#include "work_folder/block_ciphers/hill_recurrent/HillRecurrentCipher.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereOpenTextGamma/VigenereOpenTextGamma.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereCipherTextGamma/VigenereCipherTextGamma.h"
#include "work_folder/gamma_ciphers/vigenere_cipher/VigenereRepetitionGamma/VigenereRepetitionGamma.h"
#include "work_folder/gamma_ciphers/VernameCipher/VernameCipher.h"
#include <memory>

/**
 * \brief Главная функция программы. Отвечает за вывод приветствия и управление интерфейсом.
 * \return Код завершения (0 при успешном выполнении).
 */
int main()
{
    std::cout << "Welcome to the 'Historical Encryptor'!\n";
    SubFunction subfunction;
    while (true) {
        std::cout << "\nWhat operation would you like to perform?\n"
        "1. Encryption\n"
        "2. Decryption\n"
        "Enter strictly 1 or 2: ";

        char operation;
        std::cin >> operation;
        if (operation != '1' && operation != '2') {
            std::cout << "\nInvalid enter. Try again.";
            continue;
        }

        std::cout << "\nEnter the filename containing your text for your operation: ";
        std::string file_with_text;
        std::cin >> file_with_text;

        bool is_valid = validate_file_path(file_with_text);
        if (!is_valid) {
            std::cout << "\nInvalid file name. Try again.\n";
            continue;
        }

        std::string text = file_to_string(file_with_text);

        std::cout << "Now enter the path to the file where the encrypted text will be saved: ";
        std::string result_file;
        std::cin >> result_file;

        is_valid = validate_file_path(file_with_text);
        if (!is_valid) {
            std::cout << "\nInvalid file name. Try again.";
            continue;
        }

        std::cout << "\nLet's choose the cipher to work with. Select cipher type:\n"
        "1. Substitution cipher\n"
        "2. Block cipher\n"
        "3. Gamma cipher\n"
        "Enter strictly 1, 2 or 3: ";
        int cipher_type;
        std::cin >> cipher_type;

        if (cipher_type != 1 && cipher_type != 2 && cipher_type != 3) {
            std::cout << "\nInvalid enter. Try again.";
            break;
        }   

        std::cout << "\nNow choose a specific cipher from your selected category:\n"
        "Select cipher:\n";
        int chosen_cipher;
        std::string ciphertext;
        switch(cipher_type) {
            case 1: {
                std::cout << "1. Simple substitution (Caesar)\n"
                "2. Affine cipher\n"
                "3. Recurrent affine cipher\n"
                "Enter strictly 1, 2 or 3: ";
                std::cin >> chosen_cipher;

                if (chosen_cipher != 1 && chosen_cipher != 2 && chosen_cipher != 3) {
                    std::cout << "\nInvalid enter. Try again.";
                    break;
                }   

                switch(chosen_cipher) {
                    case 1: {
                        std::cout << "\nEnter encryption key.\n"
                        "Hint: the program won't accept your key if it doesn't contain all elements of the English alphabet.\n"
                        "Enter in one line without spaces or other separators: ";
                        std::string k;
                        std::cin >> k;
                        CaesarCipher caesar(k);
                        if (operation == '1') {ciphertext = caesar.caesar_encryption(text);}
                        else {ciphertext = caesar.caesar_decryption(text);}
                        break;
                    }

                    case 2: {
                        int alpha; int beta;
                        int opposite_alpha;
                        while (true)
                        {
                            std::cout << "Enter alpha: ";
                            std::cin >> alpha;
                            opposite_alpha = subfunction.modInverse(alpha, ALPHABET_SIZE);
                            if (opposite_alpha != -1) {
                                break;
                            }
                            std::cout << "Error: The alpha value and alphabet size must be coprime (their GCD should be 1)." << std::endl;
                        }
                        
                        std::cout << "Enter beta: ";
                        std::cin >> beta;
                        if (operation == '1') {AffineCoder coder(alpha, beta); 
                            ciphertext = AffineCipher(text).affine(coder);}
                        else {AffineEncoder coder(subfunction.modInverse(alpha, ALPHABET_SIZE), beta); 
                            ciphertext = AffineCipher(text).affine(coder);}
                        break;
                    }

                    case 3: {
                        int alpha1, beta1, alpha2, beta2;
                        std::cout << "Enter the first key (alpha beta): ";
                        std::cin >> alpha1 >> beta1;
                        std::cout << "Enter the second key (alpha beta): ";
                        std::cin >> alpha2 >> beta2;
                        std::array<int, 2> key1 = {alpha1, beta1};
                        std::array<int, 2> key2 = {alpha2, beta2};

                        AffineRecurrentCipher arcipher(key1, key2);
                        ciphertext = arcipher.cipher(text, operation);
                        break;
                    }
                }
                break;
            }

            case 2: {
                std::cout << "1. Hill cipher\n"
                "2. Recurrent Hill cipher\n"
                "Enter strictly 1 or 2: ";
                std::cin >> chosen_cipher;

                if (chosen_cipher != 1 && chosen_cipher != 2) {
                    std::cout << "\nInvalid enter. Try again.";
                    break;
                }  

                std::cout << "\nEnter the number of rows and columns in the key matrix (enter only a positive integer without dots or other symbols): ";
                std::string size;
                std::cin >> size;
                int key_size = std::stoi(size);

                switch(chosen_cipher) {
                    case 1: {
                        std::vector<std::vector<int>> matrix(key_size, std::vector<int>(key_size));

                        std::cout << "\nEnter the key matrix:\n"
                        "Hint: enter columns separated by spaces, and rows by pressing 'ENTER':" << std::endl;

                        enter_the_matrix(key_size, matrix);

                        std::unique_ptr<BlockCipher> key_vec = std::make_unique<HillCipher>(matrix);
                        ciphertext = key_vec->hill(text, operation);
                        break;
                    }
                    
                    
                    case 2: {
                        std::vector<std::vector<int>> matrix1(key_size, std::vector<int>(key_size));
                        std::vector<std::vector<int>> matrix2(key_size, std::vector<int>(key_size));

                        std::cout << "\nEnter the first key matrix:\n"
                        "Hint: enter columns separated by spaces, and rows by pressing 'ENTER':" << std::endl;

                        enter_the_matrix(key_size, matrix1);

                        std::cout << "\nEnter the second key matrix:\n"
                        "Hint: enter columns separated by spaces, and rows by pressing 'ENTER':" << std::endl;

                        enter_the_matrix(key_size, matrix2);

                        HillRecurrentCipher hrcipher(matrix1, matrix2);
                        ciphertext = hrcipher.hill(text, operation);

                    }
                }
                break;
            }

            case 3: {
                std::cout << "\n1. Vigenere cipher\n"
                "2. Vername cipher\n"
                "Enter strictly 1 or 2:" << std::endl;
                std::cin >> chosen_cipher;

                if (chosen_cipher != 1 && chosen_cipher != 2) {
                    std::cout << "\nInvalid enter. Try again.";
                    break;
                }  

                switch(chosen_cipher) {
                    case 1: {
                        std::cout << "\nChoose gamma generation type:\n"
                        "1. Key repetition\n"
                        "2. Opentext gamma\n"
                        "3. Ciphertext gamma\n"
                        "Enter strictly 1, 2 or 3: " << std::endl;

                        int gamma_type;
                        std::cin >> gamma_type;

                        switch(gamma_type) {
                            case 1: {
                                if (operation == '1') {ciphertext = VigenereRepetitionGamma(text, 1).ciphertext;}
                                else {ciphertext = VigenereRepetitionGamma(text, -1).ciphertext;}
                                break;
                            }

                            case 2: {
                                if (operation == '1') {ciphertext =  VigenereOpenTextGamma(text, 1).ciphertext;}
                                else {ciphertext =  VigenereCipherTextGamma(text, -1).ciphertext;}
                                break;
                            }

                            case 3: {
                                if (operation == '1') {ciphertext =  VigenereCipherTextGamma(text, 1).ciphertext;}
                                else {ciphertext =  VigenereOpenTextGamma(text, -1).ciphertext;}
                                break;
                            }
                        }

                        break;
                    }

                    case 2: {
                        if (operation == '1') {ciphertext =  VernameCipher(text, 1).ciphertext;}
                        else {ciphertext =  VernameCipher(text, -1).ciphertext;}
                        break;
                    }
                }
                break;
            }
        }
        string_to_file(result_file, ciphertext);
    }
    return 0;
}