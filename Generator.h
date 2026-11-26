#pragma once

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс для генерации целочисленных значений.
     *
     * Используется как интерфейс для различных способов заполнения матрицы:
     * случайными числами, вводом с клавиатуры или константным значением.
     */
    class Generator {
    public:
        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~Generator() = default;

        /**
         * @brief Сгенерировать очередное значение.
         * @return Сгенерированное целочисленное значение.
         */
        virtual int generate() const = 0;
    };

} // namespace miit::algebra