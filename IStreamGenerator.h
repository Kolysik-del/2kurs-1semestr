#pragma once
#include "Generator.h"
#include <istream>

namespace miit::algebra {

    /**
     * @brief Генератор, читающий целочисленные значения из входного потока.
     */
    class IStreamGenerator : public Generator {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор генератора потока ввода.
         * @param in Ссылка на входной поток (по умолчанию std::cin).
         */
        explicit IStreamGenerator(std::istream& in);

        /**
         * @brief Считать и вернуть очередное значение из потока.
         * @return Считанное целочисленное значение.
         */
        int generate() const override;
    };

} // namespace miit::algebra