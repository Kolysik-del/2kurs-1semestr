#include "Task1.h"

namespace miit::algebra {

    Task1::Task1(Matrix<int>& matrix) : Exercise{ matrix } {}

    void Task1::solve() {
        if (matrix.isEmpty()) return;
        const std::size_t rows = matrix.getRows();
        const std::size_t cols = matrix.getCols();
        for (std::size_t i = 0; i < rows; ++i) {
            std::size_t maxCol = 0;
            int maxValue = matrix[i][0];
            for (std::size_t j = 1; j < cols; ++j) {
                const int cur = matrix[i][j];
                if (cur > maxValue) { maxValue = cur; maxCol = j; }
            }
            matrix[i][maxCol] = 0;
        }
    }

} // namespace miit::algebra