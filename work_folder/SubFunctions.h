/**
 * \file
 * \brief Определение вспомогательного класса SubFunction и пользовательского исключения InvalidInputError.
 */

#pragma once
#include <vector>
#include <exception>
#include <string>

/**
 * \class SubFunction
 * \brief Содержит вспомогательные функции для работы с текстом и арифметикой по модулю.
 */
class SubFunction
{
public:
    /**
     * \brief Преобразует строку в вектор чисел, соответствующих индексам символов в алфавите.
     * \param text Входная строка, содержащая только буквы.
     * \return Вектор индексов символов.
     */
    static std::vector<int> text_in_numbers(const std::string& text);

    /**
     * \brief Преобразует вектор чисел обратно в строку.
     * \param nums Вектор индексов символов.
     * \return Строка, соответствующая вектору.
     */
    static std::string numbers_to_text(const std::vector<int>& nums);

    /**
     * \brief Реализует расширенный алгоритм Евклида.
     * \param a Первое число.
     * \param b Второе число.
     * \param x Коэффициент x такой, что ax + by = gcd(a, b).
     * \param y Коэффициент y такой, что ax + by = gcd(a, b).
     * \return Наибольший общий делитель чисел a и b.
     */
    int extendedGCD(int a, int b, int& x, int& y);

    /**
     * \brief Вычисляет мультипликативную обратную величину по модулю.
     * \param a Число, для которого ищется обратное.
     * \param m Модуль.
     * \return Обратное число по модулю m, либо -1, если оно не существует.
     */
    int modInverse(int a, int m);

    /**
     * \brief Проверяет, содержит ли строка только буквенные символы.
     * \param str Строка для проверки.
     * \return true, если строка состоит только из букв, иначе false.
     */
    bool is_alpha(const std::string& str);
};

/**
 * \class InvalidInputError
 * \brief Класс пользовательского исключения для обработки ошибок ввода.
 */
class InvalidInputError : public std::exception {
private:
    std::string message; ///< Сообщение об ошибке

public:
    /**
     * \brief Конструктор исключения с сообщением.
     * \param msg Текст сообщения об ошибке.
     */
    explicit InvalidInputError(const std::string& msg) : message(msg) {}

    /**
     * \brief Возвращает сообщение об ошибке.
     * \return C-строка с текстом ошибки.
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};
 