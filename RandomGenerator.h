#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra {

    /**
     * @brief √енератор случайных целочисленных значений в заданном диапазоне.
     */
    class RandomGenerator : public Generator {
    private:
        mutable std::mt19937 generator;
        mutable std::uniform_int_distribution<int> distribution;

    public:
        /**
         * @brief  онструктор генератора случайных чисел.
         * @param min ћинимальное возможное значение (включительно).
         * @param max ћаксимальное возможное значение (включительно).
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief —генерировать очередное случайное значение.
         * @return —лучайное число из заданного диапазона [min, max].
         */
        int generate() const override;
    };

} // namespace miit::algebra