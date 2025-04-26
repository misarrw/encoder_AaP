cmake_minimum_required(VERSION 3.10...3.25)
project(Encoder)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Добавляем исполняемый файл
add_executable(encoder_AaP
    main.cpp
    work_folder/globals.cpp
    work_folder/substitution_ciphers/caesar/CaesarCipher.cpp
    work_folder/substitution_ciphers/SubstitutionCipher.cpp
    work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.cpp
    work_folder/SubFunctions.cpp
)

add_executable(encoder_test
    encoder_test.cpp 
    work_folder/SubFunctions.cpp
    work_folder/globals.cpp
    work_folder/gamma_ciphers/vigenere_cipher/VigenereCipher.cpp
    work_folder/gamma_ciphers/vigenere_cipher/gamma_generation/repetition_gamma/RepetitionGamma.cpp
    work_folder/SubFunctions.cpp
    work_folder/substitution_ciphers/affine_recurrent/AffineRecurrentCipher.cpp
    work_folder/substitution_ciphers/SubstitutionCipher.cpp)


add_subdirectory(external)

# Присоединили doctest
target_link_libraries(encoder_test PRIVATE doctest::doctest)


# Указываем, где искать заголовки
# Для основного проекта
target_include_directories(encoder_AaP PRIVATE
    ${CMAKE_SOURCE_DIR}/work_folder
)




# Для тестового проекта
target_include_directories(encoder_test PRIVATE
    ${CMAKE_SOURCE_DIR}/work_folder
)

# Включили CMake
enable_testing()
# Зарегистрировали тест для CMake
add_test(NAME encoder_test COMMAND encoder_test --force-colors -d)