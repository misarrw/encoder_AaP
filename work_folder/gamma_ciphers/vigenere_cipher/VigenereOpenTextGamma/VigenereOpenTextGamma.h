/**
 * \file
 * \brief Заголовочный файл класса VigenereOpenTextGamma — шифр Виженера с гаммой, построенной из открытого текста.
 */

#pragma once
#include "../VigenereCipher.h"

/**
 * \class VigenereOpenTextGamma
 * \brief Вариант шифра Виженера, в котором гамма формируется из открытого текста.
 */
class VigenereOpenTextGamma : public VigenereCipher {
protected:
    /**
     * \brief Генерирует гамму, используя первый символ ключа и открытый текст.
     */
    void create_gamma() override;

    /**
     * \brief Возвращает количество символов ключа, используемых в начальной гамме.
     * \return 1 — используется только первый символ ключа.
     */
    size_t get_len_key() const override { return 1; }

public:
    /**
     * \brief Конструктор инициализирует объект, выполняет проверку ключа, создание гаммы и шифрование.
     * \param t Открытый текст для шифрования.
     * \param x Числовой параметр, используемый в формуле гаммирования.
     */
    VigenereOpenTextGamma(std::string t, int x) {
        param = x;
        text = t;
        check_key();
        create_gamma();
        cipher();
    };
};
