/**
 * \file
 * \brief Заголовочный файл класса VernameCipher — реализация шифра Вернама (одноразовый блокнот).
 */

#pragma once
#include "../GammaCipher.h"
#include <iostream>

/**
 * \class VernameCipher
 * \brief Класс реализует шифр Вернама с возможностью генерации или ручного ввода гаммы.
 *
 * При param == 1 генерирует случайную гамму.
 * При param != 1 ожидает ввод гаммы пользователем (одинаковой длины с открытым текстом).
 */
class VernameCipher : public GammaCipher {
protected:
    std::vector<int> gamma;     ///< Вектор гаммы
    std::string text;           ///< Исходный текст
    int param;                  ///< Параметр (1 — сгенерировать гамму, иначе — ввод вручную)
    size_t len_text;            ///< Длина текста

    /**
     * \brief Генерирует случайную гамму такой же длины, как текст.
     */
    void create_gamma() override;

    /**
     * \brief Возвращает текущую гамму.
     * \return Вектор значений гаммы.
     */
    std::vector<int> get_gamma() override { return gamma; }

    /**
     * \brief Возвращает исходный текст.
     * \return Ссылка на строку текста.
     */
    const std::string& get_text() const override { return text; }

    /**
     * \brief Возвращает параметр шифрования.
     * \return Ссылка на параметр.
     */
    const int& get_param() override { return param; }
public:
    /**
     * \brief Конструктор инициализирует текст, параметр и гамму (автоматически или вручную).
     * \param t Текст для шифрования.
     * \param x Параметр:
     *          - если x == 1 — гамма создаётся автоматически;
     *          - иначе — гамма запрашивается у пользователя.
     */
    VernameCipher(std::string t, int x) {
        param = x;
        text = t;
        len_text = text.size();
        if (x == 1) {
            create_gamma();
        } else {
            while (true) {
                std::cout << "Enter key: ";
                std::string gamma_text;
                std::cin >> gamma_text;
                if (len_text == gamma_text.size()) {
                    gamma = text_in_numbers(gamma_text);
                    break;
                }
                std::cout << "Error: Key length mismatch. The key should be the same size as the plaintext.";
            }
        }
        cipher();
    }
};
