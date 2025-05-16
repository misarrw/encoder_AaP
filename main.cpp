#include <iostream>
#include <cctype>
#include "work_folder\SubFunctions.h"
#include <fstream>
#include "work_folder\substitution_ciphers\caesar\CaesarCipher.h"
#include "work_folder\gamma_ciphers\vigenere_cipher\gamma_generation\opentext_gamma\OpentextGamma.h"
#include "work_folder\gamma_ciphers\vigenere_cipher\gamma_generation\\repetition_gamma\RepetitionGamma.h"
#include "work_folder\files_functions.h"
#include "work_folder\block_ciphers\BlockCipher.h"
#include "work_folder\block_ciphers\hill_cipher\HillCipher.h"
// #include "work_folder\gamma_ciphers\vigenere_cipher\gamma_generation\ciphertext_gamma"

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

        if (operation == '1') {
            std::cout << "\nGreat! Let's encrypt something!\n"
            "Enter the filename containing your text to encrypt: ";
            std::string file_with_text;
            std::cin >> file_with_text;
            std::string text = file_to_string(file_with_text);

            std::cout << "Now enter the path to the file where the encrypted text will be saved: ";
            std::string file_for_ciphertext;
            std::cin >> file_for_ciphertext;

            std::cout << "\nLet's choose the cipher to work with. Select cipher type:\n"
            "1. Substitution cipher\n"
            "2. Block cipher\n"
            "3. Gamma cipher\n"
            "Enter strictly 1, 2 or 3: ";
            char cipher_type;
            std::cin >> cipher_type;

            std::cout << "\nNow choose a specific cipher from your selected category:\n"
            "Select cipher:\n";
            char chosen_cipher;

            if (cipher_type == '1') {
                std::cout << "1. Simple substitution (Caesar)\n"
                "2. Affine cipher\n"
                "3. Recurrent affine cipher\n"
                "Enter strictly 1, 2 or 3: ";
                std::cin >> chosen_cipher;
                
                if (chosen_cipher == '1') {
                    std::cout << "\nEnter encryption key.\n"
                    "Hint: the program won't accept your key if it doesn't contain all elements of the English alphabet.\n"
                    "Enter in one line without spaces or other separators: ";
                    std::string k;
                    std::cin >> k;
                    CaesarCipher caesar(k);
                    std::string ciphertext = caesar.caesar_encryption(text);
                    string_to_file(file_for_ciphertext, ciphertext);
                }

                else if (chosen_cipher == '2') {
                    std::cout << "\nEnter alpha component of the encryption key: ";
                    char alpha;
                    std::cin >> alpha;

                    std::cout << "\nEnter beta component of the encryption key: ";
                    char beta;
                    std::cin >> beta;
                    // combine components into key
                    // key validation
                    // encryption function
                }

                else if (chosen_cipher == '3') {
                    std::cout << "Enter alpha component of the first encryption key: ";
                    int alpha1;
                    std::cin >> alpha1;

                    std::cout << "Enter beta component of the first encryption key: ";
                    int beta1;
                    std::cin >> beta1;

                    // combine components into key
                    // key validation

                    std::cout << "Enter alpha component of the second encryption key: ";
                    int alpha2;
                    std::cin >> alpha2;

                    std::cout << "Enter beta component of the second encryption key: ";
                    int beta2;
                    std::cin >> beta2;

                    // combine components into key
                    // key validation

                    // encryption function
                }
            }

            else if (cipher_type == '2') {
                std::cout << "1. Hill cipher\n"
                "2. Recurrent Hill cipher\n"
                "Enter strictly 1 or 2:";
                std::cin >> chosen_cipher;
                std::cout << "\nEnter the number of rows and columns in the key matrix (enter only a positive integer without dots or other symbols): ";
                    std::string size;
                    std::cin >> size;
                    int key_size = std::stoi(size);
                if (chosen_cipher == '1') {
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

                    BlockCipher* key_vec = new HillCipher(matrix);
                    bool if_correct = key_vec->check_key(matrix.size() * matrix[0].size(), matrix[0].size());

                    if (!if_correct) {
                        std::cout << "Your key is not square or invalid. Try again!" << std::endl;
                        delete key_vec;
                    }
                    else {
                        int option = 1;
                        std::string ciphertext = key_vec->hill(text, option);
                        string_to_file(file_for_ciphertext, ciphertext);
                    }
                    delete key_vec;
                }

                else if (chosen_cipher == '2') {
                    std::vector<std::vector<int>> matrix1(key_size, std::vector<int>(key_size));

                    std::cout << "\nEnter the first key matrix:\n"
                    "Hint: enter columns separated by spaces, and rows by pressing 'ENTER'" << std::endl;

                    for (int i = 0; i < key_size; ++i) {
                        for (int j = 0; j < key_size; ++j) {
                            std::cin >> matrix1[i][j];
                        }
                    
                    // key validation function

                    std::vector<std::vector<int>> matrix2(key_size, std::vector<int>(key_size));

                    std::cout << "Enter the second key matrix:\n"
                    "Hint: enter columns separated by spaces, and rows by pressing 'ENTER'" << std::endl;

                    for (int i = 0; i < key_size; ++i) {
                        for (int j = 0; j < key_size; ++j) {
                            std::cin >> matrix2[i][j];
                        }
                    }

                    // key validation function

                    // encryption function

                }
            }
        }

            else if (cipher_type == '3') {
                std::cout << "1. Vigenère cipher\n"
                "2. Vernam cipher\n"
                "Enter strictly 1 or 2:" << std::endl;
                std::cin >> chosen_cipher;

                if (chosen_cipher == '1') {
                    std::cout << "Enter the key: it must consist of letters, neither numbers nor other symbols" << std::endl;
                    std::string key;
                    std::cin >> key;

                    // key validation function
                    // letter-to-number conversion function

                    // condition checking key length and setting limits based on length

                    std::cout << "Choose gamma generation type:\n"
                    "1. Key repetition\n"
                    "2. Opentext gamma\n"
                    "3. Ciphertext gamma\n"
                    "Enter strictly 1, 2 or 3: " << std::endl;
                    char gamma_type;
                    std::cin >> gamma_type;

                    if (gamma_type == '1') {
                        RepetitionGamma gamma;
                        // gamma generation function
                    }

                    else if (gamma_type == '2') {
                        OpentextGamma gamma;
                        // gamma generation function
                    }

                    else if (gamma_type == '3') {
                        // CiphertextGamma gamma;
                        // gamma generation function
                    }

                    // encryption function
                }

                else if (chosen_cipher == '2') {
                    // Vernam
                }

            }
        }

        else if (operation == '2') {
            std::cout << "\nAlright! Let's decrypt your ciphertext!\n"
            "Enter the filename containing your ciphertext to decrypt: ";
            std::string file_with_ciphertext;
            std::cin >> file_with_ciphertext;
            std::string ciphertext = file_to_string(file_with_ciphertext);

            std::cout << "\nNow enter the path to the file where the original text will be saved: ";
            std::string file_for_text;
            std::cin >> file_for_text;

            std::cout << "\nLet's choose the cipher to work with. Select cipher type:\n"
            "1. Substitution cipher\n"
            "2. Block cipher\n"
            "3. Gamma cipher\n"
            "Enter strictly 1, 2 or 3: ";
            char cipher_type;
            std::cin >> cipher_type;

            std::cout << "\nNow choose a specific cipher from your selected category:\n"
            "Select cipher:\n";
            char chosen_cipher;

            if (cipher_type == '1') {
                std::cout << "1. Simple substitution (Caesar)\n"
                "2. Affine cipher\n"
                "3. Recurrent affine cipher\n"
                "Enter strictly 1, 2 or 3: ";
                std::cin >> chosen_cipher;
                
                if (chosen_cipher == '1') {
                    std::cout << "\nEnter encryption key.\n"
                    "Hint: the program won't accept your key if it doesn't contain all elements of the English alphabet.\n"
                    "Enter in one line without spaces or other separators: ";
                    std::string k;
                    std::cin >> k;
                    CaesarCipher caesar(k);
                    std::string text = caesar.caesar_decryption(ciphertext);
                    string_to_file(file_for_text, text);
                }

                else if (chosen_cipher == '2') {
                    std::cout << "\nEnter alpha component of the encryption key: ";
                    char alpha;
                    std::cin >> alpha;

                    std::cout << "\nEnter beta component of the encryption key: ";
                    char beta;
                    std::cin >> beta;
                    // combine components into key
                    // key validation
                    // encryption function
                }

                else if (chosen_cipher == '3') {
                    std::cout << "Enter alpha component of the first encryption key: ";
                    int alpha1;
                    std::cin >> alpha1;

                    std::cout << "Enter beta component of the first encryption key: ";
                    int beta1;
                    std::cin >> beta1;

                    // combine components into key
                    // key validation

                    std::cout << "Enter alpha component of the second encryption key: ";
                    int alpha2;
                    std::cin >> alpha2;

                    std::cout << "Enter beta component of the second encryption key: ";
                    int beta2;
                    std::cin >> beta2;

                    // combine components into key
                    // key validation

                    // encryption function
                }
            }

            else if (cipher_type == '2') {
                std::cout << "1. Hill cipher\n"
                "2. Recurrent Hill cipher\n"
                "Enter strictly 1 or 2:" << std::endl;
                std::cin >> chosen_cipher;
                std::cout << "Enter the number of rows and columns in the key matrix (enter only a positive integer without dots or other symbols)" << std::endl;
                    std::string size;
                    std::cin >> size;
                    int key_size = std::stoi(size);

                    if (chosen_cipher == '1') {
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
    
                        BlockCipher* key_vec = new HillCipher(matrix);
                        bool if_correct = key_vec->check_key(matrix.size() * matrix[0].size(), matrix[0].size());
    
                        if (!if_correct) {
                            std::cout << "Your key is not square or invalid. Try again!" << std::endl;
                            delete key_vec;
                        }
                        else {
                            int option = 1;
                            std::string text = key_vec->hill(ciphertext, option);
                            string_to_file(file_for_text, text);
                        }
                        delete key_vec;
                    }

                else if (chosen_cipher == '2') {
                    std::vector<std::vector<int>> matrix1(key_size, std::vector<int>(key_size));

                    std::cout << "Enter the first key matrix:\n"
                    "Hint: enter columns separated by spaces, and rows by pressing 'ENTER'" << std::endl;

                    for (int i = 0; i < key_size; ++i) {
                        for (int j = 0; j < key_size; ++j) {
                            std::cin >> matrix1[i][j];
                        }
                    
                    // key validation function

                    std::vector<std::vector<int>> matrix2(key_size, std::vector<int>(key_size));

                    std::cout << "Enter the second key matrix:\n"
                    "Hint: enter columns separated by spaces, and rows by pressing 'ENTER'" << std::endl;

                    for (int i = 0; i < key_size; ++i) {
                        for (int j = 0; j < key_size; ++j) {
                            std::cin >> matrix2[i][j];
                        }
                    }

                    // key validation function

                    // encryption function

                }
            }
        }

            else if (cipher_type == '3') {
                std::cout << "1. Vigenère cipher\n"
                "2. Vernam cipher\n"
                "Enter strictly 1 or 2:" << std::endl;
                std::cin >> chosen_cipher;

                if (chosen_cipher == '1') {
                    std::cout << "Enter the key: it must consist of letters, neither numbers nor other symbols" << std::endl;
                    std::string key;
                    std::cin >> key;

                    // key validation function
                    // letter-to-number conversion function

                    // condition checking key length and setting limits based on length

                    std::cout << "Choose gamma generation type:\n"
                    "1. Key repetition\n"
                    "2. Opentext gamma\n"
                    "3. Ciphertext gamma\n"
                    "Enter strictly 1, 2 or 3: " << std::endl;
                    char gamma_type;
                    std::cin >> gamma_type;

                    if (gamma_type == '1') {
                        RepetitionGamma gamma;
                        // gamma generation function
                    }

                    else if (gamma_type == '2') {
                        OpentextGamma gamma;
                        // gamma generation function
                    }

                    else if (gamma_type == '3') {
                        // CiphertextGamma gamma;
                        // gamma generation function
                    }

                    // encryption function
                }

                else if (chosen_cipher == '2') {
                    // Vernam
                }

            }


        }

        else {
        std::cout << "Invalid input. Please choose 1 or 2." << std::endl;
        }
    return 0;
    }
}