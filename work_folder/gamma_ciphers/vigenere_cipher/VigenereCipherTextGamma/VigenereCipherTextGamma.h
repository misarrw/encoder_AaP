/**
 * \file
 * \brief Заголовочный файл класса VigenereCipherTextGamma — модификация шифра Виженера, использующая шифртекст для генерации гаммы.
 */

#pragma once
#include "../VigenereCipher.h"

/**
 * \class VigenereCipherTextGamma
 * \brief Вариант шифра Виженера, в котором гамма строится на основе текста шифра.
 */
class VigenereCipherTextGamma : public VigenereCipher {
protected:
    /**
     * \brief Возвращает длину ключа, используемого для инициализации гаммы.
     * \return Константа 1, поскольку используется только первый символ ключа.
     */
    size_t get_len_key() const override { return 1; }

    /**
     * \brief Инициализирует гамму, добавляя первый символ ключа.
     */
    void create_gamma() override;

    /**
     * \brief Добавляет очередной зашифрованный символ в гамму.
     * \param gamma_cipher Текущая гамма.
     * \param i Индекс зашифрованного символа для добавления.
     */
    void add_char_gamma(std::vector<int>& gamma_cipher, int i) override;

public:
    /**
     * \brief Конструктор принимает текст и параметр.
     * \param t Текст для шифрования.
     * \param x Параметр шифра (используется в формуле).
     */
    VigenereCipherTextGamma(std::string t, int x) {
        param = x;
        text = t;
        check_key();
        create_gamma();
        cipher();
    }
};
