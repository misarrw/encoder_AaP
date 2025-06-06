#include <iostream>
#include <cctype>
#include "work_folder\SubFunctions.h"
#include <fstream>
#include "work_folder\substitution_ciphers\caesar\CaesarCipher.h"
#include "work_folder\files_functions.h"
#include "work_folder\block_ciphers\BlockCipher.h"
#include "work_folder\block_ciphers\hill_cipher\HillCipher.h"
#include "work_folder\gamma_ciphers\vigenere_cipher\VigenereOpenTextGamma\VigenereOpenTextGamma.h"
#include "work_folder\gamma_ciphers\vigenere_cipher\VigenereCipherTextGamma\VigenereCipherTextGamma.h"
#include "work_folder\gamma_ciphers\vigenere_cipher\VigenereRepetitionGamma\VigenereRepetitionGamma.h"
#include "work_folder\gamma_ciphers\VernameCipher\VernameCipher.h"


int main()
{
    while (true) {
        std::cout << "Welcome to the 'Historical Encryptor'!\n"
        "What operation would you like to perform?\n"
        "1. Encryption\n"
        "2. Decryption\n"
        "Enter strictly 1 or 2: ";

        char operation;
        std::cin >> operation;
        if (operation != '1' && operation != '2') {
            std::cout << "\nInvalid enter. Try again.";
            break;
        }

        std::cout << "\nEnter the filename containing your text for encryption: ";
        std::string file_with_text;
        std::cin >> file_with_text;

        bool is_valid = validate_file_path(file_with_text);
        if (!is_valid) {
            std::cout << "\nInvalid file name. Try again.";
            break;
        }

        else {
            std::string text = file_to_string(file_with_text);

            std::cout << "Now enter the path to the file where the encrypted text will be saved: ";
            std::string result_file;
            std::cin >> result_file;

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
                            std::string ciphertext;
                            if (operation == '1') {ciphertext = caesar.caesar_encryption(text);}
                            else {ciphertext = caesar.caesar_decryption(text);}
                            string_to_file(result_file, ciphertext);
                        }

                        case 2: {
                            // аффинный
                        }

                        case 3: {
                            // аффинный рекуррентный
                        }
                    }
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

                            for (int i = 0; i < key_size; ++i) {
                                std::string row_input;
                                std::cout << "Row " << i + 1 << ": ";
                                std::getline(std::cin >> std::ws, row_input);
                            
                                std::istringstream iss(row_input);
                                for (int j = 0; j < key_size; ++j) {
                                    if (!(iss >> matrix[i][j])) {
                                        std::cerr << "Invalid input for row " << i + 1 << ". Please try again.\n";
                                        --i;
                                        break;
                                    }
                                }
                            }

                            std::unique_ptr<BlockCipher> key_vec = std::make_unique<HillCipher>(matrix);
                            int option = 1;
                            std::string ciphertext = key_vec->hill(text, option);
                            string_to_file(result_file, ciphertext);
                        }

                        case 2: {
                            // хилла рекуррентный
                        }
                    }
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

                            std::string ciphertext;
                            switch(gamma_type) {
                                case 1: {
                                    ciphertext = VigenereRepetitionGamma(text, operation).ciphertext;
                                }

                                case 2: {
                                    ciphertext =  VigenereOpenTextGamma(text, operation).ciphertext;
                                }

                                case 3: {
                                    ciphertext =  VigenereCipherTextGamma(text, operation).ciphertext;
                                }
                            }

                            string_to_file(result_file, ciphertext);
                        }

                        case 2: {
                            VernameCipher(text, 1);
                        }
                    }
                }
            }
        }
    }
}