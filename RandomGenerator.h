#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra {

    /**
     * @brief Генератор случайных целочисленных значений в заданном диапазоне.
     */
    class RandomGenerator : public Generator {
    private:
        mutable std::mt19937 generator;
        mutable std::uniform_int_distribution<int> distribution;

    public:
        /**
         * @brief Конструктор генератора случайных чисел.
         * @param min Минимальное возможное значение (включительно).
         * @param max Максимальное возможное значение (включительно).
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Сгенерировать очередное случайное значение.
         * @return Случайное число из заданного диапазона [min, max].
         */
        int generate() const override;
    };

} // namespace miit::algebra