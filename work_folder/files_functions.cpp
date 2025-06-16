/**
 * \file
 * \brief Реализация функций для чтения, записи и проверки файлов.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <filesystem>

/**
 * \brief Считывает содержимое файла в строку.
 * \param file_path Путь к файлу.
 * \return Строка с содержимым файла.
 * \throws std::runtime_error Если файл не удалось открыть.
 */
std::string file_to_string(const std::string& file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + file_path);
    }

    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

/**
 * \brief Записывает строку данных в файл.
 * \param file_path Путь к файлу для записи.
 * \param data Строка с содержимым, которое будет записано.
 */
void string_to_file(const std::string& file_path, std::string& data) {
    std::ofstream file(file_path);
    file << data;
    file.close();
}

namespace fs = std::filesystem;

/**
 * \brief Проверяет, существует ли файл, и можно ли его открыть.
 *
 * Проверка включает:
 * - путь не пустой и содержит имя файла;
 * - файл существует;
 * - это обычный файл, а не директория;
 * - файл можно открыть для чтения.
 *
 * \param path Путь к файлу.
 * \return true, если файл допустим; иначе false.
 */
bool validate_file_path(const std::string& path) {
    try {
        fs::path filePath(path);

        if (filePath.empty() || !filePath.has_filename()) {
            return false;
        }

        if (!fs::exists(filePath)) {
            return false;
        }

        if (!fs::is_regular_file(filePath)) {
            return false;
        }

        std::ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }

        return true;
    }
    catch (const fs::filesystem_error&) {
        return false;
    }
}
