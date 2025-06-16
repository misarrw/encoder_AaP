/**
 * \file
 * \brief Заголовочный файл абстрактного базового класса GammaCipher для гаммирующих шифров.
 */

#pragma once
#include <vector>
#include <string>
#include "../SubFunctions.h"
#include "globals.h"

/**
 * \class GammaCipher
 * \brief Абстрактный базовый класс для реализации гаммирующих шифров.
 */
class GammaCipher : public SubFunction
{
protected:
    /**
     * \brief Генерирует и возвращает начальную гамму для шифрования.
     * \return Вектор целых чисел — последовательность гаммы.
     */
    virtual std::vector<int> get_gamma() = 0;

    /**
     * \brief Возвращает исходный текст для шифрования/дешифрования.
     * \return Ссылка на строку с текстом.
     */
    virtual const std::string& get_text() const = 0;

    /**
     * \brief Возвращает числовой параметр, участвующий в шифровании.
     * \return Ссылка на целочисленный параметр.
     */
    virtual const int& get_param() = 0;

    /**
     * \brief Обновляет гамму после каждого символа.
     * \param gamma Ссылка на текущую гамму.
     * \param i Индекс символа, добавляемого к гамме.
     */
    virtual void add_char_gamma(std::vector<int>& gamma, int i) { return; }

    /**
     * \brief Генерирует гамму с нуля (вызывается до шифрования).
     */
    virtual void create_gamma() = 0;

    /**
     * \brief Выполняет шифрование текста по текущей гамме.
     */
    void cipher();

public:
    std::string ciphertext{}; ///< Результат шифрования
    /**
     * \brief Виртуальный деструктор.
     */
    virtual ~GammaCipher() {}
};
