/**
 * \file
 * \brief Объявления функций для работы с файловой системой: чтение, запись и валидация путей.
 */

#include <string>

/**
 * \brief Считывает содержимое текстового файла и возвращает его как строку.
 * \param file_path Путь к текстовому файлу.
 * \return Строка с полным содержимым файла.
 */
std::string file_to_string(const std::string& file_path);

/**
 * \brief Записывает строку данных в указанный файл.
 * \param file_path Путь к файлу, куда будет записана строка.
 * \param data Содержимое для записи.
 */
void string_to_file(const std::string& file_path, std::string& data);

/**
 * \brief Проверяет существование и доступность пути к файлу.
 * \param filepath Путь к проверяемому файлу.
 * \return true, если путь существует и доступен, иначе false.
 */
bool validate_file_path(const std::string& filepath);
