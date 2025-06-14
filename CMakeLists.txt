
cmake_minimum_required(VERSION 3.10...3.25)
project(Encoder)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Add Armadillo via FetchContent
FetchContent_Declare(
  armadillo
  GIT_REPOSITORY https://gitlab.com/conradsnicta/armadillo-code.git
  GIT_TAG 12.0.x  # or another stable version
)
FetchContent_MakeAvailable(armadillo)

# Declare your executables
add_executable(encoder_AaP
    main.cpp
    work_folder/globals.cpp
    work_folder/substitution_ciphers/caesar/CaesarCipher.cpp
    work_folder/substitution_ciphers/SubstitutionCipher.cpp
    work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.cpp
    work_folder/substitution_ciphers/affine/AffineCipher.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereRepetitionGamma/VigenereRepetitionGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereOpenTextGamma/VigenereOpenTextGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipherTextGamma/VigenereCipherTextGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.cpp
    work_folder/gamma_ciphers/VernameCipher/VernameCipher.cpp
    work_folder/gamma_ciphers/GammaCipher.cpp
    work_folder/SubFunctions.cpp
    work_folder/block_ciphers/BlockCipher.cpp
    work_folder/block_ciphers/hill_cipher/HillCipher.cpp
    work_folder/files_functions.cpp
    work_folder/block_ciphers/hill_recurrent/HillRecurrentCipher.cpp
)

add_executable(encoder_test
    encoder_test.cpp
    work_folder/SubFunctions.cpp
    work_folder/globals.cpp
    work_folder/substitution_ciphers/caesar/CaesarCipher.cpp
    work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.cpp
    work_folder/substitution_ciphers/affine/AffineCipher.cpp
    work_folder/substitution_ciphers/SubstitutionCipher.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereRepetitionGamma/VigenereRepetitionGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereOpenTextGamma/VigenereOpenTextGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipherTextGamma/VigenereCipherTextGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.cpp
    work_folder/gamma_ciphers/VernameCipher/VernameCipher.cpp
    work_folder/gamma_ciphers/GammaCipher.cpp
    # Add these if needed by tests
    work_folder/block_ciphers/BlockCipher.cpp
    work_folder/block_ciphers/hill_cipher/HillCipher.cpp
    work_folder/block_ciphers/hill_recurrent/HillRecurrentCipher.cpp
)

add_executable(encoder_armadillo
    main.cpp
    work_folder/SubFunctions.cpp
    work_folder/globals.cpp
    work_folder/SubFunctions.cpp
    work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.cpp
    work_folder/substitution_ciphers/affine/AffineCipher.cpp
    work_folder/substitution_ciphers/SubstitutionCipher.cpp
    work_folder/substitution_ciphers/caesar/CaesarCipher.cpp
    work_folder/files_functions.cpp
    work_folder/block_ciphers/BlockCipher.cpp
    work_folder/block_ciphers/hill_cipher/HillCipher.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereRepetitionGamma/VigenereRepetitionGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereOpenTextGamma/VigenereOpenTextGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipherTextGamma/VigenereCipherTextGamma.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.cpp
    work_folder/gamma_ciphers/VernameCipher/VernameCipher.cpp
    work_folder/gamma_ciphers/GammaCipher.cpp
    work_folder/block_ciphers/hill_recurrent/HillRecurrentCipher.cpp
)

add_subdirectory(external)

# Link libraries - use the target name from the fetched Armadillo
target_link_libraries(encoder_test PRIVATE doctest::doctest armadillo)
target_link_libraries(encoder_armadillo PRIVATE armadillo)
target_link_libraries(encoder_AaP PRIVATE armadillo)

# Include directories
target_include_directories(encoder_AaP PRIVATE
    ${CMAKE_SOURCE_DIR}/work_folder
)

target_include_directories(encoder_test PRIVATE
    ${CMAKE_SOURCE_DIR}/work_folder
    ${ARMADILLO_INCLUDE_DIRS}
)

target_include_directories(encoder_armadillo PRIVATE
    ${CMAKE_SOURCE_DIR}/work_folder
)

enable_testing()
add_test(NAME encoder_test COMMAND encoder_test --force-colors -d)
