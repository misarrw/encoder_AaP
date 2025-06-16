/**
 * \file
 * \brief Заголовочный файл базового класса VigenereCipher для всех модификаций шифра Виженера.
 */

#pragma once
#include <vector>
#include <string>
#include "../GammaCipher.h"

/**
 * \class VigenereCipher
 * \brief Базовый абстрактный класс для реализации шифра Виженера и его модификаций.
 */
class VigenereCipher : public GammaCipher {
protected:
    std::string key;              ///< Ключ шифра
    std::vector<int> key_numbers; ///< Ключ, преобразованный в числовое представление
    std::vector<int> gamma;       ///< Текущая гамма
    std::string text;             ///< Текст для шифрования или дешифрования
    int param;                    ///< Параметр, используемый в гаммировании

    /**
     * \brief Возвращает длину ключа, допустимую для данной реализации.
     * \return Максимальная длина ключа.
     */
    virtual size_t get_len_key() const { return 0; }

    /**
     * \brief Возвращает текущую гамму.
     * \return Вектор целых чисел — текущая гамма.
     */
    std::vector<int> get_gamma() override { return gamma; }

    /**
     * \brief Возвращает значение параметра, используемого в гаммировании.
     * \return Ссылка на параметр.
     */
    const int& get_param() override { return param; }

    /**
     * \brief Возвращает исходный текст.
     * \return Ссылка на строку текста.
     */
    const std::string& get_text() const override { return text; }

    /**
     * \brief Запрашивает и проверяет ключ от пользователя.
     */
    virtual void check_key();

    /**
     * \brief Защищённый конструктор по умолчанию.
     */
    VigenereCipher() {}

public:
    /**
     * \brief Виртуальный деструктор.
     */
    virtual ~VigenereCipher() {}
};
