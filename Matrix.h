#pragma once
#include "Generator.h"
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace miit::algebra {

    /**
     * @brief Шаблонный класс двумерного массива (матрицы).
     * @tparam T Тип элементов матрицы.
     *
     * Реализует базовые операции с матрицей: доступ по индексу,
     * заполнение, циклические сдвиги строк, вставку и удаление строк/столбцов.
     */
    template <typename T>
    class Matrix {
    private:
        std::vector<std::vector<T>> data;
        std::size_t rows;
        std::size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию. Создает пустую матрицу.
         */
        Matrix() : data{}, rows{ 0 }, cols{ 0 } {}

        /**
         * @brief Конструктор матрицы заданного размера.
         * @param rows Количество строк.
         * @param cols Количество столбцов.
         */
        Matrix(const std::size_t rows, const std::size_t cols)
            : data(rows, std::vector<T>(cols)), rows{ rows }, cols{ cols } {
        }

        /**
         * @brief Конструктор матрицы с заполнением через генератор.
         * @param rows Количество строк.
         * @param cols Количество столбцов.
         * @param generator Генератор значений для заполнения матрицы.
         */
        Matrix(const std::size_t rows, const std::size_t cols, const Generator& generator)
            : Matrix(rows, cols) {
            fill(generator);
        }

        /**
         * @brief Конструктор копирования (по умолчанию).
         */
        Matrix(const Matrix&) = default;

        /**
         * @brief Конструктор перемещения (по умолчанию).
         */
        Matrix(Matrix&&) noexcept = default;

        /**
         * @brief Оператор присваивания копированием (по умолчанию).
         */
        Matrix& operator=(const Matrix&) = default;

        /**
         * @brief Оператор присваивания перемещением (по умолчанию).
         */
        Matrix& operator=(Matrix&&) noexcept = default;

        /**
         * @brief Деструктор (по умолчанию).
         */
        ~Matrix() = default;

        /**
         * @brief Получить ссылку на строку матрицы по индексу (неконстантный).
         * @param index Индекс строки.
         * @return Ссылка на вектор элементов строки.
         * @throw std::out_of_range Если индекс выходит за границы количества строк.
         */
        std::vector<T>& operator[](const std::size_t index) {
            if (index >= data.size()) throw std::out_of_range("Matrix: row index out of range");
            return data[index];
        }

        /**
         * @brief Получить константную ссылку на строку матрицы по индексу.
         * @param index Индекс строки.
         * @return Константная ссылка на вектор элементов строки.
         * @throw std::out_of_range Если индекс выходит за границы количества строк.
         */
        const std::vector<T>& operator[](const std::size_t index) const {
            if (index >= data.size()) throw std::out_of_range("Matrix: row index out of range");
            return data[index];
        }

        /**
         * @brief Циклический сдвиг элементов каждой строки влево.
         * @param shift Количество позиций для сдвига.
         * @return Ссылка на измененную матрицу (*this).
         */
        Matrix& operator<<(const std::size_t shift) {
            if (cols == 0) return *this;
            const std::size_t s = shift % cols;
            for (auto& row : data)
                std::rotate(row.begin(), row.begin() + static_cast<std::ptrdiff_t>(s), row.end());
            return *this;
        }

        /**
         * @brief Циклический сдвиг элементов каждой строки вправо.
         * @param shift Количество позиций для сдвига.
         * @return Ссылка на измененную матрицу (*this).
         */
        Matrix& operator>>(const std::size_t shift) {
            if (cols == 0) return *this;
            const std::size_t s = shift % cols;
            for (auto& row : data)
                std::rotate(row.begin(), row.end() - static_cast<std::ptrdiff_t>(s), row.end());
            return *this;
        }

        /**
         * @brief Получить количество строк матрицы.
         * @return Количество строк.
         */
        std::size_t getRows() const noexcept { return data.size(); }

        /**
         * @brief Получить количество столбцов матрицы.
         * @return Количество столбцов.
         */
        std::size_t getCols() const noexcept { return cols; }

        /**
         * @brief Проверить, является ли матрица пустой.
         * @return true, если матрица не содержит строк или столбцов, иначе false.
         */
        bool isEmpty() const noexcept { return data.empty() || data[0].empty(); }

        /**
         * @brief Заполнить матрицу значениями, полученными от генератора.
         * @param generator Генератор значений.
         */
        void fill(const Generator& generator) {
            for (auto& row : data)
                for (auto& element : row)
                    element = static_cast<T>(generator.generate());
        }

        /**
         * @brief Получить строковое представление матрицы.
         * @return Строка, содержащая элементы матрицы, разделенные пробелами и переносами строк.
         */
        std::string toString() const {
            std::ostringstream out;
            for (const auto& row : data) {
                for (std::size_t j = 0; j < cols; ++j) {
                    out << row[j];
                    if (j + 1 < cols) {
                        out << ' ';
                    }
                }
                out << '\n';
            }
            return out.str();
        }

        /**
         * @brief Вставить строку в матрицу по заданному индексу.
         * @param index Индекс, по которому будет вставлена строка.
         * @param row Вектор элементов новой строки.
         * @throw std::invalid_argument Если размер строки не совпадает с количеством столбцов.
         * @throw std::out_of_range Если индекс больше текущего количества строк.
         */
        void insertRow(const std::size_t index, const std::vector<T>& row) {
            if (row.size() != cols) throw std::invalid_argument("Matrix: row size mismatch");
            if (index > data.size()) throw std::out_of_range("Matrix: row index out of range");
            data.insert(data.begin() + static_cast<std::ptrdiff_t>(index), row);
            rows = data.size();
        }

        /**
         * @brief Удалить строку из матрицы по заданному индексу.
         * @param index Индекс удаляемой строки.
         * @throw std::out_of_range Если индекс выходит за границы количества строк.
         */
        void removeRow(const std::size_t index) {
            if (index >= data.size()) throw std::out_of_range("Matrix: row index out of range");
            data.erase(data.begin() + static_cast<std::ptrdiff_t>(index));
            rows = data.size();
        }

        /**
         * @brief Вставить столбец в матрицу по заданному индексу.
         * @param index Индекс, по которому будет вставлен столбец.
         * @param col Вектор элементов нового столбца.
         * @throw std::invalid_argument Если размер столбца не совпадает с количеством строк.
         * @throw std::out_of_range Если индекс больше текущего количества столбцов.
         */
        void insertCol(const std::size_t index, const std::vector<T>& col) {
            if (col.size() != data.size()) throw std::invalid_argument("Matrix: col size mismatch");
            if (index > cols) throw std::out_of_range("Matrix: col index out of range");
            for (std::size_t i = 0; i < data.size(); ++i)
                data[i].insert(data[i].begin() + static_cast<std::ptrdiff_t>(index), col[i]);
            ++cols;
        }

        /**
         * @brief Удалить столбец из матрицы по заданному индексу.
         * @param index Индекс удаляемого столбца.
         * @throw std::out_of_range Если индекс выходит за границы количества столбцов.
         */
        void removeCol(const std::size_t index) {
            if (index >= cols) throw std::out_of_range("Matrix: col index out of range");
            for (auto& row : data) row.erase(row.begin() + static_cast<std::ptrdiff_t>(index));
            --cols;
        }
    };

} // namespace miit::algebra