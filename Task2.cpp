#include "Task2.h"
#include <vector>

namespace miit::algebra {

    Task2::Task2(Matrix<int>& matrix) : Exercise{ matrix } {}

    void Task2::solve() {
        if (matrix.isEmpty()) return;
        const std::size_t rows = matrix.getRows();
        const std::vector<int> zeroRow = createZeroRow();
        for (std::size_t i = rows; i-- > 0;) {
            if (firstElementDivisibleByThree(i)) matrix.insertRow(i, zeroRow);
        }
    }

    std::vector<int> Task2::createZeroRow() const {
        return std::vector<int>(matrix.getCols(), 0);
    }

    bool Task2::firstElementDivisibleByThree(const std::size_t row) const {
        return matrix[row][0] % 3 == 0;
    }

} // namespace miit::algebra