/**
 * \file
 * \brief Заголовочный файл класса VigenereRepetitionGamma — шифр Виженера с повторяющейся гаммой.
 */

#pragma once
#include "../VigenereCipher.h"

/**
 * \class VigenereRepetitionGamma
 * \brief Вариант шифра Виженера, где гамма формируется путём многократного повторения ключа.
 */
class VigenereRepetitionGamma : public VigenereCipher {
protected:
    /**
     * \brief Генерирует гамму повторением ключа до длины текста.
     */
    void create_gamma() override;

    /**
     * \brief Возвращает длину гаммы, совпадающую с длиной текста.
     * \return Размер текста (гамма повторяется до его длины).
     */
    size_t get_len_key() const override { return text.size(); }

public:
    /**
     * \brief Конструктор. Инициализирует поля и запускает создание гаммы и шифрование.
     * \param t Текст для шифрования.
     * \param x Параметр (множитель гаммы).
     */
    VigenereRepetitionGamma(std::string t, int x) {
        param = x;
        text = t;
        check_key();
        create_gamma();
        cipher();
    };
};

