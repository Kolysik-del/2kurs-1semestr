#pragma once
#include "Generator.h"

namespace miit::algebra {

    /**
     * @brief √енератор, возвращающий посто€нное заданное значение.
     */
    class ConstantGenerator : public Generator {
    private:
        int value;

    public:
        /**
         * @brief  онструктор генератора констант.
         * @param value «начение, которое будет возвращать генератор.
         */
        explicit ConstantGenerator(const int value);

        /**
         * @brief —генерировать очередное значение (возвращает константу).
         * @return «начение, заданное при создании генератора.
         */
        int generate() const override;
    };

} // namespace miit::algebra