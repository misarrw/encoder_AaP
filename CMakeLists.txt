cmake_minimum_required(VERSION 3.10)
project(Encoder)

set(CMAKE_CXX_STANDARD 17)

# Добавляем исполняемый файл
add_executable(encoder_AaP
    main.cpp
    work_folder/globals.cpp
    work_folder/substitution_ciphers/caesar/CaesarCipher.cpp
)

# Указываем, где искать заголовки
target_include_directories(encoder_AaP PRIVATE
    ${CMAKE_SOURCE_DIR}/work_folder
)