#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Matrix.h"
#include "Task1.h"
#include "Task2.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
using namespace miit::algebra;

// ============================================================
// Тесты класса Matrix — конструкторы
// ============================================================
TEST(MatrixTest, DefaultConstructor)
{
    Matrix<int> m;
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getCols(), 0u);
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixTest, SizeConstructor)
{
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getCols(), 4u);
    EXPECT_FALSE(m.isEmpty());
    for (std::size_t i = 0; i < m.getRows(); ++i)
        for (std::size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], 0);
}

TEST(MatrixTest, ZeroSizeConstructor)
{
    Matrix<int> m(0, 0);
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getCols(), 0u);
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixTest, CopyConstructor)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 3, gen);
    Matrix<int> b = a;
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b.getCols(), 3u);
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][2], 6);
    b[0][0] = 100;
    EXPECT_EQ(a[0][0], 1);
}

TEST(MatrixTest, MoveConstructor)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 3, gen);
    Matrix<int> b = std::move(a);
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b.getCols(), 3u);
    EXPECT_EQ(b[0][0], 1);
}

// ============================================================
// Тесты класса Matrix — операторы присваивания
// ============================================================
TEST(MatrixTest, CopyAssignment)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 2, gen);
    Matrix<int> b;
    b = a;
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b.getCols(), 2u);
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][1], 4);
    b[0][0] = 99;
    EXPECT_EQ(a[0][0], 1);
}

TEST(MatrixTest, MoveAssignment)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 2, gen);
    Matrix<int> b;
    b = std::move(a);
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][1], 4);
}

TEST(MatrixTest, SelfAssignment)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 2, gen);
    a = a;
    EXPECT_EQ(a[0][0], 1);
    EXPECT_EQ(a[1][1], 4);
}

// ============================================================
// Тесты класса Matrix — заполнение
// ============================================================
TEST(MatrixTest, FillWithConstant)
{
    ConstantGenerator gen(7);
    Matrix<int> m(2, 3, gen);
    for (std::size_t i = 0; i < m.getRows(); ++i)
        for (std::size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], 7);
}

TEST(MatrixTest, FillWithNegativeConstant)
{
    ConstantGenerator gen(-5);
    Matrix<int> m(3, 3, gen);
    for (std::size_t i = 0; i < m.getRows(); ++i)
        for (std::size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], -5);
}

TEST(MatrixTest, FillFromStream)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixTest, FillFromStreamWithNegative)
{
    std::istringstream input("-1 -2 3 -4 5 -6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    EXPECT_EQ(m[0][0], -1);
    EXPECT_EQ(m[0][1], -2);
    EXPECT_EQ(m[1][2], -6);
}

// ============================================================
// Тесты класса Matrix — доступ по индексу
// ============================================================
TEST(MatrixTest, IndexOperator)
{
    std::istringstream input("10 20 30 40");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);
    EXPECT_EQ(m[0][0], 10);
    EXPECT_EQ(m[1][1], 40);
    m[0][1] = 99;
    EXPECT_EQ(m[0][1], 99);
}

TEST(MatrixTest, ConstIndexOperator)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    const Matrix<int> m(2, 2, gen);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTest, IndexOutOfRangeThrows)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW(m[2][0], std::out_of_range);
}

// ============================================================
// Тесты класса Matrix — сдвиги строк
// ============================================================
TEST(MatrixTest, ShiftLeft)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    m << 1;
    EXPECT_EQ(m[0][0], 2);
    EXPECT_EQ(m[0][1], 3);
    EXPECT_EQ(m[0][2], 1);
    EXPECT_EQ(m[1][0], 5);
    EXPECT_EQ(m[1][2], 4);
}

TEST(MatrixTest, ShiftLeftByZero)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    m << 0;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
}

TEST(MatrixTest, ShiftRight)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    m >> 1;
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[0][1], 1);
    EXPECT_EQ(m[0][2], 2);
    EXPECT_EQ(m[1][0], 6);
    EXPECT_EQ(m[1][2], 5);
}

TEST(MatrixTest, ShiftLeftByFullWidth)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    m << 3;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
}

// ============================================================
// Тесты класса Matrix — toString
// ============================================================
TEST(MatrixTest, ToStringBasic)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);
    EXPECT_EQ(m.toString(), "1 2\n3 4\n");
}

TEST(MatrixTest, ToStringEmpty)
{
    Matrix<int> m;
    EXPECT_EQ(m.toString(), "");
}

TEST(MatrixTest, ToStringNegative)
{
    std::istringstream input("-1 -2 -3 -4");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);
    EXPECT_EQ(m.toString(), "-1 -2\n-3 -4\n");
}

// ============================================================
// Тесты класса Matrix — insertRow / removeRow
// ============================================================
TEST(MatrixTest, InsertRow)
{
    Matrix<int> m(2, 3);
    std::vector<int> row = { 9, 9, 9 };
    m.insertRow(1, row);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[1][0], 9);
    EXPECT_EQ(m[1][2], 9);
}

TEST(MatrixTest, InsertRowAtBeginning)
{
    Matrix<int> m(2, 2);
    std::vector<int> row = { 7, 7 };
    m.insertRow(0, row);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[0][0], 7);
}

TEST(MatrixTest, InsertRowWrongSizeThrows)
{
    Matrix<int> m(2, 3);
    std::vector<int> row = { 1, 2 };
    EXPECT_THROW(m.insertRow(0, row), std::invalid_argument);
}

TEST(MatrixTest, RemoveRow)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    m.removeRow(0);
    EXPECT_EQ(m.getRows(), 1u);
    EXPECT_EQ(m[0][0], 4);
    EXPECT_EQ(m[0][2], 6);
}

TEST(MatrixTest, RemoveRowOutOfRangeThrows)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.removeRow(5), std::out_of_range);
}

// ============================================================
// Тесты класса Matrix — insertCol / removeCol
// ============================================================
TEST(MatrixTest, RemoveCol)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);
    m.removeCol(1);
    EXPECT_EQ(m.getCols(), 2u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 3);
    EXPECT_EQ(m[1][1], 6);
}

TEST(MatrixTest, RemoveColOutOfRangeThrows)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.removeCol(5), std::out_of_range);
}

TEST(MatrixTest, InsertCol)
{
    Matrix<int> m(2, 2);
    std::vector<int> col = { 5, 6 };
    m.insertCol(1, col);
    EXPECT_EQ(m.getCols(), 3u);
    EXPECT_EQ(m[0][1], 5);
    EXPECT_EQ(m[1][1], 6);
}

TEST(MatrixTest, InsertColWrongSizeThrows)
{
    Matrix<int> m(2, 2);
    std::vector<int> col = { 1, 2, 3 };
    EXPECT_THROW(m.insertCol(0, col), std::invalid_argument);
}

// ============================================================
// Тесты Задания 1: макс. элемент строки -> 0
// ============================================================
TEST(Task1Test, BasicExample)
{
    //  5 -2  3
    //  1  8 -4
    //  7 -1  6
    std::istringstream input("5 -2 3 1 8 -4 7 -1 6");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);  // максимум строки 0 — это 5
    EXPECT_EQ(m[1][1], 0);  // максимум строки 1 — это 8
    EXPECT_EQ(m[2][0], 0);  // максимум строки 2 — это 7
    EXPECT_EQ(m[0][1], -2);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 1);
    EXPECT_EQ(m[1][2], -4);
    EXPECT_EQ(m[2][1], -1);
    EXPECT_EQ(m[2][2], 6);
}

TEST(Task1Test, AllNegative)
{
    // -3 -7 -2
    // -5 -1 -8
    std::istringstream input("-3 -7 -2 -5 -1 -8");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][2], 0);  // максимум строки 0 — это -2 (не -7!)
    EXPECT_EQ(m[1][1], 0);  // максимум строки 1 — это -1
    EXPECT_EQ(m[0][0], -3);
    EXPECT_EQ(m[0][1], -7);
    EXPECT_EQ(m[1][0], -5);
    EXPECT_EQ(m[1][2], -8);
}

TEST(Task1Test, EqualMaximaReplaceFirst)
{
    // 4 -4 1
    std::istringstream input("4 -4 1");
    IStreamGenerator gen(input);
    Matrix<int> m(1, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);   // первый из равных максимумов
    EXPECT_EQ(m[0][1], -4);
    EXPECT_EQ(m[0][2], 1);
}

TEST(Task1Test, MaxIsZero)
{
    // -5 -2 0
    std::istringstream input("-5 -2 0");
    IStreamGenerator gen(input);
    Matrix<int> m(1, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], -5);
    EXPECT_EQ(m[0][1], -2);
    EXPECT_EQ(m[0][2], 0);
}

TEST(Task1Test, SingleRow)
{
    // 3 -7 2 -5
    std::istringstream input("3 -7 2 -5");
    IStreamGenerator gen(input);
    Matrix<int> m(1, 4, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], -7);
    EXPECT_EQ(m[0][2], 2);
    EXPECT_EQ(m[0][3], -5);
}

TEST(Task1Test, SingleColumn)
{
    // 3
    // -7
    // 2
    // -5
    std::istringstream input("3 -7 2 -5");
    IStreamGenerator gen(input);
    Matrix<int> m(4, 1, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[2][0], 0);
    EXPECT_EQ(m[3][0], 0);
}

TEST(Task1Test, EmptyMatrixNoThrow)
{
    Matrix<int> m;
    Task1 task(m);
    EXPECT_NO_THROW(task.solve());
}

// ============================================================
// Тесты Задания 2
// ============================================================
TEST(Task2Test, BasicExample)
{
    // 1 2
    // 9 3   <- первый элемент делится на 3
    // 4 5
    std::istringstream input("1 2 9 3 4 5");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 4u);
    EXPECT_EQ(m.getCols(), 2u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][0], 0);  // вставленная строка
    EXPECT_EQ(m[1][1], 0);
    EXPECT_EQ(m[2][0], 9);
    EXPECT_EQ(m[3][0], 4);
}

TEST(Task2Test, NoMatchingRows)
{
    // 1 2
    // 4 5
    // 7 8
    std::istringstream input("1 2 4 5 7 8");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[2][0], 7);
}

TEST(Task2Test, AllRowsMatch)
{
    // 3 1
    // 6 2
    // 9 3
    std::istringstream input("3 1 6 2 9 3");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 6u);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[2][0], 0);
    EXPECT_EQ(m[2][1], 0);
    EXPECT_EQ(m[3][0], 6);
    EXPECT_EQ(m[4][0], 0);
    EXPECT_EQ(m[4][1], 0);
    EXPECT_EQ(m[5][0], 9);
}

TEST(Task2Test, NegativeDivisibleByThree)
{
    // -3 1   <- делится на 3
    //  2 2
    //  6 3   <- делится на 3
    std::istringstream input("-3 1 2 2 6 3");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 5u);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[1][0], -3);
    EXPECT_EQ(m[2][0], 2);
    EXPECT_EQ(m[3][0], 0);
    EXPECT_EQ(m[4][0], 6);
}

TEST(Task2Test, FirstElementIsZero)
{
    // 0 5   <- 0 делится на 3
    // 1 6
    std::istringstream input("0 5 1 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[2][0], 1);
}

TEST(Task2Test, SingleRowDivisible)
{
    std::istringstream input("3 3");
    IStreamGenerator gen(input);
    Matrix<int> m(1, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 2u);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 3);
}

TEST(Task2Test, EmptyMatrixNoThrow)
{
    Matrix<int> m;
    Task2 task(m);
    EXPECT_NO_THROW(task.solve());
}

// ============================================================
// Комбинированный тест: Task1 и Task2 работают независимо
// ============================================================
TEST(CombinedTest, Task1ThenTask2_Independent)
{
    // Исходная матрица:
    // 5 -2  3
    // 1  8 -4
    // 7 -1  6
    std::istringstream input("5 -2 3 1 8 -4 7 -1 6");
    IStreamGenerator gen(input);
    Matrix<int> original(3, 3, gen);

    // Task1 работает на копии
    Matrix<int> forTask1 = original;
    Task1 t1(forTask1);
    t1.solve();

    // Проверяем результат Task1
    EXPECT_EQ(forTask1[0][0], 0);  // максимум строки 0 (5) ? 0
    EXPECT_EQ(forTask1[1][1], 0);  // максимум строки 1 (8) ? 0
    EXPECT_EQ(forTask1[2][0], 0);  // максимум строки 2 (7) ? 0

    // Task2 работает на ДРУГОЙ копии исходной матрицы
    Matrix<int> forTask2 = original;
    Task2 t2(forTask2);
    t2.solve();

    // Первые элементы исходной матрицы: 5, 1, 7
    // Ни один не делится на 3, поэтому Task2 НЕ вставляет строки
    EXPECT_EQ(forTask2.getRows(), 3u);  // размер не изменился
    EXPECT_EQ(forTask2[0][0], 5);       // первый элемент строки 0
    EXPECT_EQ(forTask2[1][0], 1);       // первый элемент строки 1
    EXPECT_EQ(forTask2[2][0], 7);       // первый элемент строки 2
}

// Дополнительный тест: Task2 видит первоначальные значения
TEST(CombinedTest, Task2SeesOriginalValues)
{
    // Матрица, где первые элементы делятся на 3:
    // 3  1  2
    // 6 -4  5
    // 9  0 -1
    std::istringstream input("3 1 2 6 -4 5 9 0 -1");
    IStreamGenerator gen(input);
    Matrix<int> original(3, 3, gen);

    // Task1 меняет максимумы на 0
    Matrix<int> forTask1 = original;
    Task1 t1(forTask1);
    t1.solve();

    // После Task1: первые элементы стали 0, 0, 0 (все делятся на 3)
    EXPECT_EQ(forTask1[0][0], 0);
    EXPECT_EQ(forTask1[1][0], 0);
    EXPECT_EQ(forTask1[2][0], 0);

    // Task2 работает на исходной матрице (копии)
    Matrix<int> forTask2 = original;
    Task2 t2(forTask2);
    t2.solve();

    // Первые элементы исходной: 3, 6, 9 — все делятся на 3
    // Task2 вставит нулевые строки перед каждой
    EXPECT_EQ(forTask2.getRows(), 6u);  // 3 исходные + 3 вставленные

    // Проверяем структуру: нулевая строка, затем исходная
    EXPECT_EQ(forTask2[0][0], 0);  // вставленная
    EXPECT_EQ(forTask2[1][0], 3);  // исходная строка 0
    EXPECT_EQ(forTask2[2][0], 0);  // вставленная
    EXPECT_EQ(forTask2[3][0], 6);  // исходная строка 1
    EXPECT_EQ(forTask2[4][0], 0);  // вставленная
    EXPECT_EQ(forTask2[5][0], 9);  // исходная строка 2
}