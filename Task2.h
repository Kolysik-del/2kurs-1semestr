#pragma once
#include "Exercise.h"
#include <vector>

namespace miit::algebra {

    /**
     * @brief Реализация Задания 2
     *
     * Задача: Вставить перед всеми строками, первый элемент которых делится на 3, строку из нулей.
     */
    class Task2 : public Exercise {
    public:
        /**
         * @brief Конструктор задания.
         * @param matrix Ссылка на матрицу для обработки.
         */
        explicit Task2(Matrix<int>& matrix);

        /**
         * @brief Выполнить вставку нулевых строк перед строками, первый элемент которых кратен 3.
         */
        void solve() override;

    private:
        /**
         * @brief Создать вектор нулей размером с количество столбцов матрицы.
         * @return Вектор, заполненный нулями.
         */
        std::vector<int> createZeroRow() const;

        /**
         * @brief Проверить, делится ли первый элемент заданной строки на 3.
         * @param row Индекс проверяемой строки.
         * @return true, если элемент кратен 3, иначе false.
         */
        bool firstElementDivisibleByThree(const std::size_t row) const;
    };

} // namespace miit::algebra