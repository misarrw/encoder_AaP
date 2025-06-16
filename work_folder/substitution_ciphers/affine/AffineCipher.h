/**
 * \file
 * \brief Заголовочный файл с определением класса AffineCipher — шифра на основе аффинного преобразования.
 */

#pragma once
#include "../SubstitutionCipher.h"
#include <array>

/**
 * \class Affine
 * \brief Абстрактная структура, определяющая интерфейс аффинного преобразования.
 *
 * Содержит параметры alpha (множитель) и beta (смещение) и чисто виртуальную функцию cipher().
 */
class Affine {
public:
    int alpha; ///< Множитель alpha, должен быть взаимно прост с ALPHABET_SIZE
    int beta;  ///< Смещение beta

    /**
     * \brief Конструктор базового класса.
     * \param alpha Множитель.
     * \param beta Смещение.
     */
    Affine(int alpha, int beta) : alpha(alpha), beta(beta) {}

    /**
     * \brief Виртуальный деструктор.
     */
    virtual ~Affine() {}

    /**
     * \brief Чисто виртуальная функция шифрования/дешифрования.
     * \param index Позиция символа в алфавите.
     * \return Новое значение позиции после преобразования.
     */
    virtual int cipher(int& index) = 0;
};

/**
 * \class AffineCipher
 * \brief Класс реализует аффинное шифрование и дешифрование текста.
 */
class AffineCipher : public SubstitutionCipher {
public:
    std::string text; ///< Текст, подлежащий шифрованию или дешифрованию

    /**
     * \brief Конструктор, принимающий текст.
     * \param text Входной текст.
     */
    AffineCipher(const std::string& text);

    /**
     * \brief Шифрует или дешифрует текст с использованием заданного объекта Affine.
     * \param coder Объект с параметрами alpha и beta, реализующий метод cipher().
     * \return Результат шифрования или дешифрования.
     */
    std::string affine(Affine& coder);
};

/**
 * \class AffineCoder
 * \brief Реализация аффинного преобразования для шифрования.
 */
class AffineCoder : public Affine {
public:
    /**
     * \brief Конструктор.
     * \param alpha Множитель.
     * \param beta Смещение.
     */
    AffineCoder(int alpha, int beta) : Affine(alpha, beta) {}

    /**
     * \brief Выполняет обратное преобразование индекса.
     * \param index Входной индекс символа.
     * \return Расшифрованный индекс.
     */
    int cipher(int& index) override;
};

/**
 * \class AffineEncoder
 * \brief Реализация аффинного преобразования для дешифрования.
 */
class AffineEncoder : public Affine {
public:
    /**
     * \brief Конструктор.
     * \param alpha Множитель.
     * \param beta Смещение.
     */
    AffineEncoder(int alpha, int beta) : Affine(alpha, beta) {}

    /**
     * \brief Выполняет прямое преобразование индекса.
     * \param index Входной индекс символа.
     * \return Зашифрованный индекс.
     */
    int cipher(int& index) override;
};
