#pragma once
#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Реализация Задания 1
     *
     * Задача: Заменить максимальный элемент каждой строки нулем.
     */
    class Task1 : public Exercise {
    public:
        /**
         * @brief Конструктор задания.
         * @param matrix Ссылка на матрицу для обработки.
         */
        explicit Task1(Matrix<int>& matrix);

        /**
         * @brief Выполнить замену максимальных элементов строк на ноль.
         */
        void solve() override;
    };

} // namespace miit::algebra