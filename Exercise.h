#pragma once
#include "Matrix.h"

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс для учебных заданий над матрицей.
     *
     * Агрегирует ссылку на матрицу и предоставляет интерфейс для решения задачи.
     */
    class Exercise {
    protected:
        Matrix<int>& matrix;

    public:
        /**
         * @brief Конструктор задания.
         * @param matrix Ссылка на матрицу, над которой будет выполняться задание.
         */
        explicit Exercise(Matrix<int>& matrix);

        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~Exercise() = default;

        /**
         * @brief Чисто виртуальный метод для решения конкретного задания.
         */
        virtual void solve() = 0;
    };

} // namespace miit::algebra