#include <iostream>
#include <locale>
#include <memory>
#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

constexpr int RANDOM_MIN = -100;
constexpr int RANDOM_MAX = 100;

/**
 * @brief Способы заполнения матрицы.
 */
enum class FillMethod { Random = 1, Manual = 2, Constant = 3, Zeros = 4 };

/**
 * @brief Точка входа в демонстрационную программу.
 *
 * Инициализирует матрицу выбранным способом, выводит её на экран,
 * а затем последовательно применяет Задание 1 и Задание 2 (Вариант 6)
 * к независимым копиям исходной матрицы.
 *
 * @return Код завершения программы (0 при успехе, 1 при ошибке ввода).
 */
int main() {
    setlocale(LC_ALL, "Russian");

    long long n_ll = 0, m_ll = 0;
    std::cout << "Введите n и m: ";

    // Защита от некорректного ввода (отрицательные или слишком большие числа)
    if (!(std::cin >> n_ll >> m_ll) || n_ll < 0 || m_ll < 0 || n_ll > 1000 || m_ll > 1000) {
        std::cout << "Некорректные размеры матрицы\n";
        return 1;
    }
    const std::size_t n = static_cast<std::size_t>(n_ll);
    const std::size_t m = static_cast<std::size_t>(m_ll);

    std::cout << "Способ заполнения:\n"
        "1 - случайные\n"
        "2 - с клавиатуры\n"
        "3 - константа\n"
        "4 - нулями\n"
        "Ваш выбор: ";
    int input = 0;
    std::cin >> input;
    const auto choice = static_cast<FillMethod>(input);

    std::unique_ptr<Generator> generator;
    switch (choice) {
    case FillMethod::Random:
        generator = std::make_unique<RandomGenerator>(RANDOM_MIN, RANDOM_MAX);
        break;
    case FillMethod::Manual:
        std::cout << "Введите " << n * m << " целых чисел:\n";
        generator = std::make_unique<IStreamGenerator>(std::cin);
        break;
    case FillMethod::Constant: {
        int value = 0;
        std::cout << "Введите константу: ";
        std::cin >> value;
        generator = std::make_unique<ConstantGenerator>(value);
        break;
    }
    case FillMethod::Zeros:
        generator = std::make_unique<ConstantGenerator>(0);
        break;
    default:
        std::cout << "Неверный выбор\n";
        return 1;
    }

    try {
        // Создаем первоначальную матрицу
        Matrix<int> original(n, m, *generator);
        std::cout << "\nИсходная матрица:\n" << original.toString();

        // Task1 — работает с исходной матрицой
        Matrix<int> forTask1 = original;
        Task1 task1(forTask1);
        task1.solve();
        std::cout << "\nПосле Задания 1 (макс. элемент строки -> 0):\n"
            << forTask1.toString();

        // Task2 — работает с исходной матрицой
        Matrix<int> forTask2 = original;
        Task2 task2(forTask2);
        task2.solve();
        std::cout << "\nПосле Задания 2 (вставка нулевой строки перед строками,"
            " первый элемент которых делится на 3):\n"
            << forTask2.toString();
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}